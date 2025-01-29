#include "EndHeliSpline.h"
#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"

AEndHeliSpline::AEndHeliSpline(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
    this->TeleportWhenStarted = false;
    this->UseHorizontalMove = false;
    this->MaxPitchDegree = 15.00f;
    this->MaxTurn = 1.00f;
    this->MaxSpeed = 500.00f;
    this->Deceleration = 0.60f;
    this->LookAtType = EndHeliLookAtType::MoveDirection;
    this->HorizontalMoveDistMax = 1000.00f;
    this->CameraRailComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SequencerBaseComponent"));
    this->DebugShowSpline = false;
    this->CurrentWeight = 0.00f;
    this->CameraRailComponent->SetupAttachment(RootComponent);
}


