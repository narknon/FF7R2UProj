#include "EndCameraSequenceActor.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"

AEndCameraSequenceActor::AEndCameraSequenceActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    this->CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    this->LevelSequence = NULL;
    this->BlendInTime = 0.00f;
    this->BlendInOption = EAlphaBlendOption::CircularInOut;
    this->BlendOutTime = 0.00f;
    this->BlendOutOption = EAlphaBlendOption::CircularInOut;
    this->CameraComponent->SetupAttachment(RootComponent);
}

void AEndCameraSequenceActor::PlaySequence() {
}

void AEndCameraSequenceActor::OnPlayerFinished() {
}


