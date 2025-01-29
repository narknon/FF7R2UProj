#include "EndStreamingVolume.h"

AEndStreamingVolume::AEndStreamingVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bColored = true;
    this->UnloadMargin = 2500.00f;
    this->StreamingVolumeType = EEndStreamingVolumeType::Default;
    this->TargetRotationDegree = 0.00f;
    this->bForce = false;
    this->bWorldOffsetRoot = false;
    this->bRoot = false;
    this->bDisabled = false;
    this->bActiveOnCheckPaused = false;
    this->bDefaultHidden = false;
    this->bCheckCameraPosition = false;
    this->bActivateDevBattle = false;
    this->bWorldToAnotherMain = false;
    this->bAnotherMainToWorld = false;
    this->ActivateProgress = 0;
    this->ShowProgress = 0;
    this->DeactivateProgress = 0;
    this->StreamingTarget = EEndStreamingVolumeTargetType::All;
    this->RenderingScene = EEndRenderingScene::Default;
}

void AEndStreamingVolume::WaitLoadingStreamingLevels(const UObject* WorldContextObject, FLatentActionInfo LatentInfo, bool NoErrMsg) {
}

void AEndStreamingVolume::ShowHideStreamingLevels(bool bShow, bool bHideDrawOnly) {
}

void AEndStreamingVolume::ShowHideInsteadLevels(bool bShow, bool bHideDrawOnly) {
}

void AEndStreamingVolume::EnableStreamingVolume(bool bEnable) {
}


