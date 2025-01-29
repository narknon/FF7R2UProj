#include "WallRunningBlockBoxVolume.h"

UWallRunningBlockBoxVolume::UWallRunningBlockBoxVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bForceHitToJump = false;
    this->bDisableWallCorrect = false;
}


