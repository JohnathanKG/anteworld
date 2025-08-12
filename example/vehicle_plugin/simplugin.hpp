#pragma once

#include <comm/intergen/ifc.h>

// wrap in special comments to inject into the generated interface header too
//  can also use /*ifc{ ... }ifc*/ to include only in the client header

/*ifc{
#include <ot/vehicle_physics.h>
}ifc*/
#include <ot/vehicle_physics.h>


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

    ifc_class(xt::engine, "ifc/");

    ifc_fn ot::vehicle_params init_chassis(const coid::token &params) override;
    ifc_fn void init_vehicle(bool reload) override;
    ifc_fn void update_frame(float dt, float engine, float brake, float steering,
                       float parking) override;
    ifc_fn void update_actions_script(float dt,
                               const coid::range<int32> &actbuf) override;
                               

  private:
    void fill_wheel_params(ot::wheel &wheel_params);
    void fill_vehicle_params(ot::vehicle_params &vehicle_params);

    bool Started;
    bool Emer;
    int EngDir;
    int Lturn;
    int Rturn;
    double Time;

    static int FLwheel;
    static int FRwheel;
    static int RLwheel;
    static int RRwheel;
    static int SteerWheel;
    static int SpeedGauge;
    static int AccelPedal;
    static int BrakePedal;
    static int DriverDoor;
    static int SrcOnOff;
    static int SrcEngOn;
    /// mod action
    static int32 mod_action;
};
