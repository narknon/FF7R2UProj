#include "EndLocationVolume.h"

AEndLocationVolume::AEndLocationVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bColored = true;
    this->UntouchMargin = 100.00f;
    this->LocationVolumeType = EEndLocationVolumeType::Default;
    this->bDisabled = false;
    this->bForce = false;
    this->bStateObject = false;
    this->bChangeCamera = false;
    this->bDisableFieldAttack = false;
    this->bDisableChocoboRide = false;
    this->bDisableBuggyRide = false;
    this->bDisplayLocationName = false;
    this->bDisplayMiniMap = false;
    this->bSafeArea = false;
    this->bDisableDodge = false;
    this->bDisableAutoJump = false;
    this->bDisableFallByInput = false;
    this->bDisableJumpByInput = false;
    this->bDisableVaultByInput = false;
    this->bChangeMovementType = false;
    this->EscapeMargin = 1500.00f;
    this->bDisplayDummyLocationName = false;
    this->bDisplayLocationNameAtLeaving = false;
    this->bOldOverlapBehavior = false;
    this->bDisableCollisionWaiting = false;
    this->LevelLoaderShowSliceLimitMilliSeconds = 0;
    this->CameraSettingID = TEXT("LocationNormal");
    this->CameraSettingPriority = EEndLocationVolumeCameraPriority::Priority3;
    this->SpecificMoveType = EEndSpecificMoveType::Empty;
    this->DashType = EEndDashType::Enable;
    this->SunglassStateOverwrite = EEndBarretSunglassStateOverwrite::None;
}

void AEndLocationVolume::EnableLocationVolume(bool bEnable) {
}


