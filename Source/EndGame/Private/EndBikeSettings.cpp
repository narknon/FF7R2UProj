#include "EndBikeSettings.h"

UEndBikeSettings::UEndBikeSettings() {
    this->TurnAngularSpeed = 1.00f;
    this->TurnAngularSpeedOnPlayerInput = 6.10f;
    this->BikeYawRotationSpeed = 22.50f;
    this->MaxTurnAngleToRollAngleFactor = 0.40f;
    this->BikeGravityScale = 2.00f;
    this->DitchRoughness = 5.00f;
    this->DitchRoughnessInterpSpeed = 500.00f;
    this->SlideRateInterpSpeed = 2.70f;
    this->BikeBlendSpaceMultiplier = 1.20f;
    this->bShowBikeDebugScreenInfo = false;
    this->BikeWindStrengthMultiplier = 30.00f;
    this->BikeWindFrequency = 30.00f;
    this->BikeWindAmplitude = 30.00f;
    this->BikeRagdollSmallHitStrength = 100.00f;
    this->BikeRagdollLargeHitStrength = 250.00f;
    this->BikeMaxBankAngle = 40.00f;
    this->BikeBankAngleInterpIncreaseSpeed = 3.00f;
    this->BikeBankAngleInterpDecreaseSpeed = 6.00f;
    this->BikePlayerAdditiveBlendspaceSpeedMultiplier = 3.00f;
    this->BikeRiderBlendSpaceCurve = EAlphaBlendOption::CircularInOut;
}


