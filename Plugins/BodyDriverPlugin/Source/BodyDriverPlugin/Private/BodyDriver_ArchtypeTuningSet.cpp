#include "BodyDriver_ArchtypeTuningSet.h"

UBodyDriver_ArchtypeTuningSet::UBodyDriver_ArchtypeTuningSet() {
    this->UseArchType = false;
    this->ArchetypeIsSelf = false;
    this->UseBaseForExplosions = true;
    this->UseBoundsInsteadOfPushes = false;
    this->ForceFrontWoundGrabs = false;
    this->UseSideHeadShotForHeadAlways = false;
    this->DisableReachForWound = false;
    this->DisableBrace = false;
    this->DisableWindmill = false;
    this->MoveClavicleHitsToUpperArm = false;
    this->MoveLowerLegHitsToThighs = false;
    this->MoveNeckHitsToHead = false;
    this->OverrideFallenLimitBlendRate = -1.00f;
    this->FallenBaseInitialBoundScale = 0.70f;
    this->ArchetypeJointSpeedClamp = -1.00f;
    this->HandAndForearmsCountsAsNonFootOnGround = true;
    this->AppendagesCountsAsNonFootOnGround = false;
    this->ExplosionForceScale = 1.00f;
    this->PatchInitialDistance = 0.30f;
    this->PatchInitialDistanceMultiplierForNonExplosions = 1.00f;
    this->PatchMoveRate = 1.00f;
    this->PatchMoveRateMultiplierForNonExplosions = 1.00f;
    this->PatchSize = 0.50f;
    this->PatchSizeMultiplierForNonExplosions = 1.00f;
    this->PatchMinDist = 0.40f;
    this->ArchetypeInitialBoundScale = 1.00f;
    this->UseArchTypeForDebugImpulsesTuning = true;
    this->UseArchTypeForApplyImpulseTuning = true;
    this->UseArchTypeForApplyExplosionTuning = false;
    this->SwitchToFallSlopeAngle = 30.00f;
    this->ChangeFallSlopAngleBasedOnMovement = true;
    this->SwitchToFallSlopeAngleTrue = 50.00f;
    this->SwitchToFallSlopeAngleTrueIfBase = 50.00f;
}


