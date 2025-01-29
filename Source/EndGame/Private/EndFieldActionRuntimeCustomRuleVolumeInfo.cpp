#include "EndFieldActionRuntimeCustomRuleVolumeInfo.h"

FEndFieldActionRuntimeCustomRuleVolumeInfo::FEndFieldActionRuntimeCustomRuleVolumeInfo() {
    this->bActive = false;
    this->bEnableFallHeightMax = false;
    this->EnableFallHeightMax = 0.00f;
    this->bEnableFallPlaneDistanceMax = false;
    this->EnableFallPlaneDistanceMax = 0.00f;
    this->bEnableJumpUpHeightMax = false;
    this->EnableJumpUpHeightMax = 0.00f;
    this->bEnableJumpUpPlaneDistanceMax = false;
    this->EnableJumpUpPlaneDistanceMax = 0.00f;
    this->bEnableFenceFallHeightMax = false;
    this->EnableFenceFallHeightMax = 0.00f;
    this->bEnableVaultStartHeight = false;
    this->EnableVaultStartHeight = 0.00f;
    this->bUseNavHeavySearch = 0.00f;
    this->bUseNavHeavySearch2 = false;
    this->bLifeStreamEdge = false;
    this->bDownTargetIsLookAt = false;
    this->bEnableLookDownFrontDistance = false;
    this->LookDownFrontDistance = 0.00f;
    this->bParkourOnlyChocoboSwampArea = false;
    this->bEnableStairToFenceParkour = false;
    this->bEnableToSlopePlaneJump = false;
    this->bIgnoreFenceBumpyBlock = false;
    this->bFenceToNarrowArea = false;
    this->bIgnoreJumpFootAreaCheck = false;
    this->bEnableSwimToSwimJump = false;
    this->bRuntimeBlockCharaCollisionCheck = false;
    this->VolumeInfoVersion = 0;
}

