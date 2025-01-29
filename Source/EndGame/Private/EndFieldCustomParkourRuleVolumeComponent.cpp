#include "EndFieldCustomParkourRuleVolumeComponent.h"

UEndFieldCustomParkourRuleVolumeComponent::UEndFieldCustomParkourRuleVolumeComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bCanEverAffectNavigation = false;
    this->bEnableJumpUpHeightMax = false;
    this->EnableJumpUpHeightMax = 350.00f;
    this->bEnableJumpUpPlaneDistanceMax = false;
    this->EnableJumpUpPlaneDistanceMax = 300.00f;
    this->bEnableFallHeightMax = false;
    this->EnableFallHeightMax = 1000.00f;
    this->bEnableFallPlaneDistanceMax = false;
    this->EnableFallPlaneDistanceMax = 300.00f;
    this->bEnableFallFenceHeightMax = false;
    this->EnableFallFenceHeightMax = 150.00f;
    this->bEnableVaultStartHeight = false;
    this->EnableVaultStartHeight = 120.00f;
    this->bUseNavHeavySearch = false;
    this->bLifeStreamEdge = false;
    this->bDownTargetIsLookAt = false;
    this->bEnableLookDownFrontDistance = false;
    this->LookDownFrontDistance = 150.00f;
    this->bParkourOnlyChocoboSwampArea = false;
    this->bEnableStairToFenceParkour = false;
    this->bEnableToSlopePlaneJump = false;
    this->bIgnoreFenceBumpyBlock = false;
    this->bFenceToNarrowArea = false;
    this->bIgnoreJumpFootAreaCheck = false;
    this->bEnableSwimToSwimJump = false;
    this->bRuntimeBlockCharaCollisionCheck = false;
}


