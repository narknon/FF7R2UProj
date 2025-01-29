#include "EndCharacterAnimInstance.h"

UEndCharacterAnimInstance::UEndCharacterAnimInstance() {
    this->RootMotionMode = ERootMotionMode::RootMotionFromEverything;
    this->CenterBoneOffsetHeightResetSpeed = 3.00f;
    this->PlayRate = 1.00f;
    this->BlendInputSpeed = 0.00f;
    this->LastBlendInputSpeed = 0.00f;
    this->BlendInputDirection = 0.00f;
    this->BlendInputFootStep = 0.00f;
    this->BlendInputStrafingX = 0.00f;
    this->BlendInputStrafingY = 0.00f;
    this->WalkType = EEndAnimWalkType::Run;
    this->LandingRate = 1.00f;
    this->bRequestedImmediateUpdateLandingRate = false;
    this->MoveToRotationRateMin = 480.00f;
    this->OverrideRotationRate = -1.00f;
    this->RotationRateScale = 1.00f;
    this->RootMotionTranslationScale = 1.00f;
    this->RootMotionTranslationUpScale = 1.00f;
    this->RootMotionRotationScale = 1.00f;
    this->RequestedBehaviorMode = EEndAnimBehaviorMode::Neutral;
    this->ActualCurrentBehaviorMode = EEndAnimBehaviorMode::Neutral;
    this->CurrentBehaviorMode = EEndAnimBehaviorMode::Neutral;
    this->CautionAnimType = EEndCautionAnimType::AsNeutral;
    this->bEnabledSwitchBehaviorRunningFullBodyBlend = false;
    this->bEnabledSwitchBehaviorWalkCancelBlend = false;
    this->bGuardOverrideIdle = true;
    this->RequestedLocomotionState = EEndLocomotionState::Idle;
    this->RequestedLocomotionStateTimer = 0.00f;
    this->CurrentLocomotionState = EEndLocomotionState::Idle;
    this->LastLocomotionState = EEndLocomotionState::Idle;
    this->CurrentLocomotionStateTimer = 0.00f;
    this->bEnabledJogState = false;
    this->bEnabledStrafingWalk = false;
    this->bUseBlendSpaceAccelOnNeutral = false;
    this->bUseBlendSpaceAccelOnBattle = false;
    this->bUseBlendSpaceTurnOnNeutral = false;
    this->bUseBlendSpaceTurnOnBattle = false;
    this->bUseBlendSpaceStrafingWalkLoopOnNeutral = false;
    this->bUseBlendSpaceStrafingWalkLoopOnBattle = false;
    this->bUseZeroTurnAlways = false;
    this->ZeroTurnRotationRate = 60.00f;
    this->bUseNeutralOnly = false;
    this->bResetRotationOnWalkRunStart = false;
    this->bWeaponVisibilityOnNeutral = true;
    this->bWeaponVisibilityOnBattle = true;
    this->bEnabledDeadLaunch = true;
    this->bEnabledBodyDriverAdditiveDamage = false;
    this->PoseMatchingType = EEndAnimPoseMatchingType::Default;
    this->CustomPoseMatchingFunction = EEndAnimBehaviorMatchingType::DeltaLocalSpaceRotationMax;
    this->bPlayingCutScene = false;
    this->bPlayingDialogue = false;
    this->bPlayingMobPrefab = false;
    this->bRequestedPoseTransition = false;
    this->RequestedPoseTransitionBlendTime = -1.00f;
    this->RequestedPoseTransitionBlendTimeLowPriority = -1.00f;
    this->RequestedPoseTransitionBlendTimeMin = -1.00f;
    this->HipOffsetWithIK = 0.00f;
    this->LipMapDefault = NULL;
    this->LipMapLoud = NULL;
    this->LipMapSmile = NULL;
}

EEndLocomotionAnimGroup UEndCharacterAnimInstance::GetLocomotionAnimGroupFromCache(EEndLocomotionState LocomotionState) const {
    return EEndLocomotionAnimGroup::Idle;
}


