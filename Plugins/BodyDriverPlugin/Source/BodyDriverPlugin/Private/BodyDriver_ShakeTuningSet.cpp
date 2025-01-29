#include "BodyDriver_ShakeTuningSet.h"

UBodyDriver_ShakeTuningSet::UBodyDriver_ShakeTuningSet() {
    this->UseShake = false;
    this->LinkSpread = 9;
    this->PelvisLinkSpread = 1;
    this->BlendOutTimeStart = 0.50f;
    this->BlendOutDuration = 0.30f;
    this->JointStrengthInitial = 1000.00f;
    this->JointStrengthFinal = 2000.00f;
    this->JointStrengthBlendTime = 1.00f;
    this->ArmStiffnessMult = 0.20f;
    this->MinSubsequentHitStrengthMultiplier = 0.00f;
    this->ConstraintReturnLinVel = 0.50f;
    this->ConstraintReturnAngVel = 3.00f;
    this->AccelerationStrength = 0.70f;
    this->ResetBlendTimeOnSubsequentHits = false;
    this->ImpulseReductionFactor = 0.40f;
    this->ImpactReductionFactor = 0.40f;
    this->UseShakeForLiveExplosions = false;
    this->ExplosionBlendOutTimeStart = 0.30f;
    this->ExplosionBlendOutDuration = 1.00f;
    this->RunningMinSpeed = -1.00f;
    this->BlendOutTimeStartRunning = 0.50f;
    this->BlendOutDurationRunning = 0.30f;
    this->JointStrengthInitialRunning = 1000.00f;
    this->JointStrengthFinalRunning = 2000.00f;
    this->JointStrengthBlendTimeRunning = 1.00f;
    this->ArmStiffnessMultRunning = 0.20f;
    this->MinSubsequentHitStrengthMultiplierRunning = 0.00f;
    this->ResetBlendTimeOnSubsequentHitsRunning = false;
    this->ImpulseReductionFactorRunning = 0.40f;
    this->ImpactReductionFactorRunning = 0.40f;
}


