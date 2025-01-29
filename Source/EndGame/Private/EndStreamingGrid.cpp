#include "EndStreamingGrid.h"

AEndStreamingGrid::AEndStreamingGrid(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->GridSize = 20000.00f;
    this->BaseLoadDistance = 30000.00f;
    this->BaseUnloadMargin = 2500.00f;
    this->ForCollisionStreaming = false;
    this->ForCollisionStreamingToCollisionAsset = false;
    this->bCheckedHeightCollisionStream = false;
    this->ThresholdCheckedHeightCollisionStream = 8000.00f;
    this->NoWaitCollisionStreaming = false;
    this->StreamingTarget = EEndStreamingVolumeTargetType::All;
    this->bDisabled = false;
}

void AEndStreamingGrid::PauseStreamingGrid(bool bEnable) {
}

void AEndStreamingGrid::EnableStreamingGrid(bool bEnable) {
}


