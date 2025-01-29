#include "Explosion.h"

FExplosion::FExplosion() {
    this->Enabled = false;
    this->UseBaseRagdollRegardless = false;
    this->UseImpulseDataAsWell = false;
    this->SkipLinearVelocityControl = false;
    this->SkipBaseDataVelocityClamp = false;
    this->MinLinearMagnitude = 0.00f;
    this->MaxLinearMagnitude = 0.00f;
    this->LinearForceApplyTime = 0.00f;
    this->ClosestDistanceToScaleMagnitude = 0.00f;
    this->FarthestDistanceToScaleMagnitude = 0.00f;
    this->MinAngleFromHorizon = 0.00f;
    this->MaxAngleFromHorizon = 0.00f;
    this->AvoidFrontAngle = 0.00f;
    this->AvoidBackAngle = 0.00f;
    this->LinearMagnitudeForContactExplosions = 0.00f;
    this->AngleFromHorizonOverrideForContactExplosions = 0.00f;
    this->RotationOppositeOfExplosionDirection = false;
    this->RotationUseDesiredBodyVelocity = false;
    this->RotationConstrainOtherRotVelocity = false;
    this->RotationSpeedForContactExplosion = 0.00f;
    this->RotationStartTime = 0.00f;
    this->RotationDuration = 0.00f;
    this->UseOverrideBodyControl = false;
}

