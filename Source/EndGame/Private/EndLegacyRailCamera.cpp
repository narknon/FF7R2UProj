#include "EndLegacyRailCamera.h"
#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"

AEndLegacyRailCamera::AEndLegacyRailCamera(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
    this->CameraRailComponent = CreateDefaultSubobject<USplineComponent>(TEXT("CameraRailComponent"));
    this->RailCameraSequencerData = NULL;
    this->UseRelativeSpace = false;
    this->BaseLocationType = ERelativeCameraBase::ActorBase;
    this->DebugShowSpline = false;
    this->UseCameraCut = true;
    this->_PrevWeight = -1.00f;
    this->PlayTime = 5.00f;
    this->DebugTime = 0.00f;
    this->TurnFieldCamera = false;
    this->TurnFieldCameraToLeaderRotation = false;
    this->NeedDeffredCalculate = false;
    this->CameraRailComponent->SetupAttachment(RootComponent);
}


