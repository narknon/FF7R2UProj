#include "EndAnimNotifyStateBikeRotateYaw.h"

UEndAnimNotifyStateBikeRotateYaw::UEndAnimNotifyStateBikeRotateYaw() {
    this->Type = EEndBikeRotateYawType::LookAtTarget;
    this->bUseAcceleration = false;
    this->RotateSpeed = 1.00f;
    this->RotateMaxSpeed = 90.00f;
    this->RotateAcceleration = 60.00f;
    this->RotateArrivalTime = 0.50f;
    this->FloatParam1 = 0.00f;
}


