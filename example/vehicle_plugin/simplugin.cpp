#pragma once

#include "simplugin.hpp"
#include "comm/commtypes.h"
#include "comm/intergen/ifc.h"
#include "comm/log/logger.h"

#include <array>
#include <glm/gtc/quaternion.hpp>
#include <ot/dynamic_object.h>
#include <ot/explosions.h>
#include <ot/location_cfg.h>
#include <ot/static_object.h>
#include <ot/vehicle_cfg.h>
#include <ot/vehicle_physics.h>

ot::wheel wheel_params;
ot::vehicle_params physics_params;

const double PI = 3.141592653589793;
std::array<double, 100> globalData;
// Static member must be defined outside class body (it doesn't need to be equal
// to anything for now, because we want to define it in init_chassis()).
uint simplugin::RevMask;
uint simplugin::BrakeMask;
uint simplugin::TurnLeftMask;
uint simplugin::TurnRightMask;
uint simplugin::MainLightOffset;
int simplugin::FLwheel;
int simplugin::FRwheel;
int simplugin::RLwheel;
int simplugin::RRwheel;
int simplugin::SteerWheel;
int simplugin::SpeedGauge;
int simplugin::AccelPedal;
int simplugin::BrakePedal;
int simplugin::DriverDoor;
int simplugin::SndStarter;
int simplugin::SndEngON;
int simplugin::SndEngOFF;
int simplugin::SrcOnOff;
int simplugin::SrcEngOn;

namespace {
IFC_REGISTER_CLIENT(simplugin)
}

simplugin::simplugin() {}

void simplugin::update_actions_script(float dt,
                                      const coid::range<int32> &actbuf) {
    for (const int8 act : actbuf) {
        if (act == mod_act) {
            coidlog_info("action", "mod button pressed");
        }
    }
}

ot::vehicle_params simplugin::init_chassis(const coid::token &params) {
    mod_act = register_event_ext("ot/player/mod");
    ot::wheel *wheelParam = new ot::wheel();
    wheelParam->radius1 = 0.31515f; // outer tire radius [m]
    wheelParam->width = 0.2f;       // tire width [m]
    wheelParam->suspension_max =
        0.1f; // max. movement up from default position [m]
    wheelParam->suspension_min =
        -0.12f; // max. movement down from default position [m]
    wheelParam->suspension_stiffness =
        30.0f; // suspension stiffness coefficient
    wheelParam->damping_compression =
        0.4f; // damping coefficient for suspension compression
    wheelParam->damping_relaxation =
        0.12f;              // damping coefficient for suspension relaxation
    wheelParam->grip = 1.f; // relative tire grip compared to an avg. tire, +-1
    wheelParam->slip_lateral_coef =
        1.5f; // lateral slip multiplier, relative to
              // the computed longitudinal tire slip
    wheelParam->differential =
        true; // true if the wheel is paired with another through a differential
    // Add wheel with vertical suspension (along z axis) using add_wheel()
    // function
    //  1.param - wheel joint/bone pivot
    //  2.param - wheel structure
    //  returns ID of the wheel
    FLwheel = add_wheel("tire_l0", *wheelParam);
    FRwheel = add_wheel("tire_r0", *wheelParam);
    RLwheel = add_wheel("tire_l1", *wheelParam);
    RRwheel = add_wheel("tire_r1", *wheelParam);

    // Get joint/bone ID for given bone name, using get_joint_id() function
    //  param - bone name
    //  returns joint/bone id or -1 if doesn't exist
    SteerWheel = get_geomob(0)->get_joint("steering_wheel");
    SpeedGauge = get_geomob(0)->get_joint("dial_speed");
    AccelPedal = get_geomob(0)->get_joint("pedal_accelerator");
    BrakePedal = get_geomob(0)->get_joint("pedal_brake");
    DriverDoor = get_geomob(0)->get_joint("door_l0");
    // Return parameters
    ot::vehicle_params *vp = new ot::vehicle_params();

    vp->mass = 1120.0f;                        // vehicle mass [kg]
    vp->com_offset = float3(0.0f, 0.0f, 0.3f); // center of mass offset
    vp->clearance = 0.f; // clearance from ground, default wheel radius
    vp->clearance = 0.f; // clearance in front and back (train bumpers)
    vp->steering.bone_ovr =
        "steering_wheel";        // steering wheel bone name override, default
                                 // "steering_wheel"
    vp->steering.radius = 0.17f; // steering wheel radius, if 0 disabled
    vp->steering.grip_angle = 0.15f; // grip angular offset in degrees
    vp->steering.steering_thr =
        50.f; // speed [km/h] at which the steering speed is reduced by 60%
    vp->steering.centering_thr =
        20.f; // speed [km/h] when the centering acts at 60% already

    return *vp;
}

void simplugin::init_vehicle(bool reload) {
    // Initialize variables for your instance (use "this" keyword for changes to
    // affect only current instance)
    this->Emer = false;
    this->Started = false;
    this->Time = 0.f;
    this->Lturn = 0;
    this->Rturn = 0;
    this->EngDir = 1;

    // Get geomob interface
    this->Geom = get_geomob(0);
    // Get sound interface
    this->Sounds = sound();

    // Set FPS camera position
    set_fps_camera_pos({-0.8f, 3.4f, 2.3f});
}

float turret_axis = 0, mantlet_axis = 0;
float turret_rot = 0, mantlet_rot = 0, armor_pitch = 0;
float engine_force = 27000.f;
float brake_force = 28000.f;
float wheel_friction = 200.f;

void simplugin::update_frame(float dt, float throttle, float brake,
                             float steering, float parking) {
    float speed_kmh = this->speed() * 3.6f; // convert speed from m/s to km/h

    float applied_engine_force = engine_force * abs(throttle);
    this->wheel_force(-1, applied_engine_force);

    this->steer(FLwheel, steering);
    this->steer(FRwheel, steering);

    float applied_wheel_friction = brake_force * brake + wheel_friction;
    this->wheel_brake(-1, applied_wheel_friction);

    turret_rot += turret_axis * 0.4 * dt;
    mantlet_rot += mantlet_axis * 0.1 * dt;
}
