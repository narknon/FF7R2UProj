#include "EndChocoboJetSettingVolume.h"

AEndChocoboJetSettingVolume::AEndChocoboJetSettingVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bDisableMoveOnlyNavMesh = false;
    this->bFakeWaterSurface = false;
    this->bHeightRestrict = false;
    this->bApplyEvenIfCharacterOver = false;
    this->bEnableAutoMoveOverNavMeshTimeOut = false;
    this->OverrideAutoMoveOverNavMeshCheckDistance = -1.00f;
}


