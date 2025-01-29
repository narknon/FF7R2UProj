#include "EndNavModifierPeekCameraVolume.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "EndNavModifierComponent.h"

AEndNavModifierPeekCameraVolume::AEndNavModifierPeekCameraVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    this->bUseDuctBlendIn = true;
    this->ResponseAreaID = TEXT("rpaPeekCamera");
    this->ResponseAreaPlayerID = TEXT("rpaPeekCameraPlayer");
    this->RangeComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RangeComponent"));
    this->TargetIconComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TargetIconComponent"));
    this->CameraComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CameraComponent"));
    this->ModifierVolume = CreateDefaultSubobject<UEndNavModifierComponent>(TEXT("Modifier"));
    this->CameraComponent->SetupAttachment(RootComponent);
    this->RangeComponent->SetupAttachment(RootComponent);
    this->TargetIconComponent->SetupAttachment(RootComponent);
}


