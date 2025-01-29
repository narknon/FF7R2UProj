#include "EndTinyBroncoMovementSetting.h"

UEndTinyBroncoMovementSetting::UEndTinyBroncoMovementSetting() {
    this->ForwardMaxSpeed = 60.00f;
    this->ForwardAccel = 15.00f;
    this->ForwardBrake = 10.00f;
    this->NeutralFriction = 5.00f;
    this->LimitSpeedOnCollisionKph = 40.00f;
    this->RotationForwardOffset = -100.00f;
    this->MaxYawSpeed = 70.00f;
    this->YawAcceleration = 120.00f;
    this->YawDeceleration = 200.00f;
    this->YawFriction = 30.00f;
    this->ValidAngleTowardNormalForSpeedLimitVolume = 60.00f;
    this->LimitNormalLength = 500.00f;
    this->MaxLimitSteeringDistance = 1500.00f;
    this->BeginForceSteeringTime = 1.00f;
    this->MaxSpeedInArea = 30.00f;
    this->MaxLimitSpeedDistance = 2000.00f;
    this->BeginForceSpeedTime = 1.00f;
    this->ForwardBrakeOnParking = 500.00f;
    this->EnablePhysicsBreakSpeedKph = 40.00f;
    this->BeginLoopVibration = 0.50f;
    this->BeginHitVibrationSpeed = 30.00f;
    this->LockOnSiteShowWidgetMaxDistance = 100000.00f;
    this->LockOnSiteMinDistShowSubIconWidget = 10000.00f;
    this->BeginDuringMoveStateSpeedKph = 30.00f;
    this->EndDuringMoveStateSpeedKph = 10.00f;
    this->bEnableDrift = true;
    this->ForwardBrakeOnDrift = 0.00f;
    this->EnableStartDriftSpeed = 10.00f;
    this->ForwardMinSpeedOnDrift = 100.00f;
    this->ForwardAccelToMinSpeedOnDrift = 50.00f;
    this->DriftRecoveryTimer = 1.00f;
    this->MaxYawSpeedOnDrift = 120.00f;
    this->YawAccelerationOnDrift = 200.00f;
    this->DriftRecoveryInputSteeringSpeed = 1.00f;
    this->DriftRecoveryInputBrakeSpeed = 0.50f;
    this->DriftEndTimeAfterNoInput = 1.00f;
    this->LimitedSpeedFrictionScaleOnDrift = 0.30f;
    this->AccelerationToReachRequestedVelocityBuffer = 10.00f;
    this->ForceRotationSpeedToRotateVelocityToRequestVelocity = 5.00f;
    this->MaxYawSpeedOnEndParking = 30.00f;
}


