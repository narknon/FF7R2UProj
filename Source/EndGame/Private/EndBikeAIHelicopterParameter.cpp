#include "EndBikeAIHelicopterParameter.h"

FEndBikeAIHelicopterParameter::FEndBikeAIHelicopterParameter() {
    this->Move_DefaultYow = 0.00f;
    this->Move_DefaultPitch = 0.00f;
    this->Move_BaseHeight = 0.00f;
    this->Move_WithinRoadSlide = 0.00f;
    this->Move_MaxPitchAngle = 0.00f;
    this->Move_MaxPitchSpeed = 0.00f;
    this->Move_PitchDefaultSpeed = 0.00f;
    this->Move_MaxSlideRollAngle = 0.00f;
    this->Move_WallHeight = 0.00f;
    this->Move_CenterObstacleHeight = 0.00f;
    this->Move_SplineOffsetForCalcCurvature = 0.00f;
    this->Move_CurvatureMaxDeltaYaw = 0.00f;
    this->Move_MaxSlideOnNotAttack = 0.00f;
    this->Atk_SelectPlayerAsTargetRate = 0;
    this->Atk_HitPointOfCancelAttack = 0;
    this->LookAt_RecoveryDelayTime = 0.00f;
    this->LookAt_YawSpeed = 0.00f;
    this->LookAt_YawAccel = 0.00f;
    this->LookAt_YawArrivalTime = 0.00f;
    this->GunFire_SpeedForFirstStep = 0.00f;
    this->GunFire_DistanceForFirstStep = 0.00f;
    this->GunFire_MaxTimeOfFitstStep = 0.00f;
    this->GunFire_CorrectionRate = 0.00f;
    this->GunFire_YawLimit = 0.00f;
    this->GunFire_Interval = 0.00f;
    this->Obstacle_BeginAvoidLength = 0.00f;
    this->StopToExit_SlideInterpSpeed = 0.00f;
    this->StopToExit_HeightSpeed = 0.00f;
    this->StopToExit_RelativeDistance = 0.00f;
    this->StopToExit_RemoveTimer = 0.00f;
    this->TransitionNoAttack_DamageValue = 0;
    this->TransitionNoAttack_TimeValue = 0.00f;
}

