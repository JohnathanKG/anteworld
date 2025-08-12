#pragma once

#include "simplugin.hpp"
#include "comm/commtypes.h"
#include "comm/intergen/ifc.h"

#include <ot/vehicle_cfg.h>
#include <ot/vehicle_physics.h>

ot::wheel wheel_params;
ot::vehicle_params physics_params;

int simplugin::FLwheel;
int simplugin::FRwheel;
int simplugin::RLwheel;
int simplugin::RRwheel;
int simplugin::SteerWheel;
int simplugin::SpeedGauge;
int simplugin::AccelPedal;
int simplugin::BrakePedal;
int simplugin::DriverDoor;
int simplugin::SrcOnOff;
int simplugin::SrcEngOn;

int simplugin::mod_action;

namespace {

    IFC_REGISTER_CLIENT(simplugin)
}

simplugin::simplugin() {}

void simplugin::fill_wheel_params(ot::wheel &wheel_params) {
    wheel_params.radius1 = 0.31515f;
    wheel_params.width = 0.2f;
    wheel_params.suspension_max = 0.1f;
    wheel_params.suspension_min = -0.12f;
    wheel_params.suspension_stiffness = 30.0f;
    wheel_params.damping_compression = 0.4f;
    wheel_params.damping_relaxation = 0.12f;
    wheel_params.grip = 1.f;
    wheel_params.slip_lateral_coef = 1.5f;
    wheel_params.differential = true;

    FLwheel = add_wheel("tire_l0", wheel_params);
    FRwheel = add_wheel("tire_r0", wheel_params);
    RLwheel = add_wheel("tire_l1", wheel_params);
    RRwheel = add_wheel("tire_r1", wheel_params);
}

void simplugin::fill_vehicle_params(ot::vehicle_params &vehicle_params) {
    vehicle_params.mass = 1120.0f;
    vehicle_params.com_offset = float3(0.0f, 0.0f, 0.3f);
    vehicle_params.clearance = 0.f;
    vehicle_params.clearance = 0.f;
    vehicle_params.steering.bone_ovr = "steering_wheel";

    vehicle_params.steering.radius = 0.17f;
    vehicle_params.steering.grip_angle = 0.15f;
    vehicle_params.steering.steering_thr = 50.f;
    vehicle_params.steering.centering_thr = 20.f;
}

void simplugin::update_actions_script(float dt,
                                      const coid::range<int32> &actbuf) {
    for (const int8 act : actbuf) {
        if (act == this->mod_action) {
            fire(float3(-0.9f, 9.4f, 9.3f), float3(0.0f, 1.0f, 0.0f), 100.0f,
                 10.0f, float3(1.0f, 1.0f, 1.0f), pkg::InvalidBoneId);
            coidlog_info("action", "mod button pressed");
        }
    }
}

ot::vehicle_params simplugin::init_chassis(const coid::token &params) {
    this->mod_action = this->register_event_ext("ot/player/mod");

    this->fill_wheel_params(wheel_params);

    SteerWheel = get_geomob(0)->get_joint("steering_wheel");
    SpeedGauge = get_geomob(0)->get_joint("dial_speed");
    AccelPedal = get_geomob(0)->get_joint("pedal_accelerator");
    BrakePedal = get_geomob(0)->get_joint("pedal_brake");
    DriverDoor = get_geomob(0)->get_joint("door_l0");

    ot::vehicle_params *vp = new ot::vehicle_params();
    this->fill_vehicle_params(*vp);
    return *vp;
}

void simplugin::init_vehicle(bool reload) {
    this->Emer = false;
    this->Started = false;
    this->Time = 0.f;
    this->Lturn = 0;
    this->Rturn = 0;
    this->EngDir = 1;

    set_fps_camera_pos({-0.8f, 3.4f, 2.3f});
}

void simplugin::update_frame(float dt, float throttle, float brake,
                             float steering, float parking) {

    this->steer(FLwheel, steering);
    this->steer(FRwheel, steering);
}
