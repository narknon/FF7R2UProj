#include "EndFrogGuysGimmickActor.h"
#include "Components/SceneComponent.h"
#include "EndFrogGuysTriggerComponent.h"

AEndFrogGuysGimmickActor::AEndFrogGuysGimmickActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    this->TriggerComponent = CreateDefaultSubobject<UEndFrogGuysTriggerComponent>(TEXT("TriggerComponent"));
    this->bIsToRotate = false;
    this->bIncreaseAngularVelocityLinearly = false;
    this->ExtraRotationAnglePerAngularVelocity = 0.00f;
    this->GimmickMotorSound = NULL;
    this->TriggerComponent->SetupAttachment(RootComponent);
}


