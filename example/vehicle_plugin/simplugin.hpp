#pragma once

#include <comm/intergen/ifc.h>

// wrap in special comments to inject into the generated interface header too
//  can also use /*ifc{ ... }ifc*/ to include only in the client header

// ifc{
#include <ot/gameob.h>
#include <ot/vehicle_physics.h>

//}ifc

// These variables can be global and initialized, as they are only used in
// statements and calculations, they will not be changed later, therefore they
// are marked as const.
const uint MaxKmh = 200;
const float SpeedGaugeMin = 10.0f;
const float RadPerKmh = 0.018325957f;
const float EngineForce = 25000.0f;
const float BrakeForce = 5000.0f;
const float ForceLoss = EngineForce / (0.2f * MaxKmh + 1.f);
/// Plugin's base implementation class, exposing a xt::engine interface

class simplugin : public ot::vehicle_physics {

  public:
    simplugin();
    ot::vehicle_params init_chassis(const coid::token &params) override;
    void init_vehicle(bool reload) override;
    void update_frame(float dt, float engine, float brake, float steering,
                      float parking) override;
    void update_actions_script(float dt,
                               const coid::range<int32> &actbuf) override;

  private:
    // Declare variables
    bool Started;
    bool Emer;
    int EngDir;
    int Lturn;
    int Rturn;
    int32 mod_act = 0;
    double Time;

    // Use static keyword, so that the variable can be shared across all
    // instances (familiar to creating global variable) without it, the
    // variables would be defined only for the 1. instance/vehicle, other
    // instances would have variables set to 0, because they are defined in
    // init_chassis(), which is called only the first time. Use only for
    // variables, that will be shared across all instances/vehicles and will not
    // be changed later (should be defined in init_chassis)
    static uint RevMask;
    static uint BrakeMask;
    static uint TurnLeftMask;
    static uint TurnRightMask;
    static uint MainLightOffset;
    static int FLwheel;
    static int FRwheel;
    static int RLwheel;
    static int RRwheel;
    static int SteerWheel;
    static int SpeedGauge;
    static int AccelPedal;
    static int BrakePedal;
    static int DriverDoor;
    static int SndStarter;
    static int SndEngON;
    static int SndEngOFF;
    static int SrcOnOff;
    static int SrcEngOn;

    // Spot and point light parameters
    ot::light_params LightParams =
        ot::light_params(); // Initializes all fields to 0

    // Geom and Sounds are smart pointers, pointing to geomob and sound groups,
    // they are used for managing reference-counted objects
    iref<ot::geomob> Geom = nullptr;
    iref<ot::sndgrp> Sounds = nullptr;
};
