#include "EndEnvironmentPhysImpulseParam.h"

FEndEnvironmentPhysImpulseParam::FEndEnvironmentPhysImpulseParam() {
    this->bIsRadialImpulse = false;
    this->Radius = 0.00f;
    this->Falloff = RIF_Constant;
    this->Magnitude = 0.00f;
    this->bVelChange = false;
    this->bMakeShrapnelDestroyPhysics = false;
}

