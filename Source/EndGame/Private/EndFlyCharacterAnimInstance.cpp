#include "EndFlyCharacterAnimInstance.h"

UEndFlyCharacterAnimInstance::UEndFlyCharacterAnimInstance() {
    this->AdditiveFlyVerticalVelocityIdle = 150.00f;
    this->ScaleFlyVerticalVelocityIdle = 1.00f;
    this->AdditiveFlyVerticalVelocityWalk = 0.00f;
    this->ScaleFlyVerticalVelocityWalk = 1.00f;
    this->AdditiveFlyVerticalVelocityRun = 0.00f;
    this->ScaleFlyVerticalVelocityRun = 1.00f;
    this->VerticalMovementDeltaRotationInterpSpeed = 5.00f;
    this->InertiaAccelerationInterpSpeed = 0.00f;
    this->InertiaDecelerationInterpSpeed = 0.00f;
    this->InertiaDeltaTranslationInterpSpeed = 0.00f;
    this->InertiaDeltaRotaionInterpSpeed = 0.00f;
    this->bEnableIdleMovementOnGround = false;
    this->bUseIdleOnWalk = false;
    this->bUseTurnMotionOnIdleWalk = false;
    this->AdditiveVelocityOnWalk = 0.00f;
    this->FlyVerticalCorrectAngleRateWalk = 0.00f;
    this->FlyVerticalCorrectAngleRateRun = 0.00f;
    this->FlyVerticalCorrectAngleRateDash = 0.00f;
}


