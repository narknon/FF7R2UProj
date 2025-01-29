#include "EndFieldActionChocoboJumpBoxActor.h"
#include "EndFieldActionTriggerComponent.h"
#include "EndNavModifierComponent.h"

AEndFieldActionChocoboJumpBoxActor::AEndFieldActionChocoboJumpBoxActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->EnterVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("EnterVolume"));
    this->ExitVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("ExitVolume"));
    this->ModifierVolume = CreateDefaultSubobject<UEndNavModifierComponent>(TEXT("Modifier"));
    this->DummyFloorComponent = NULL;
    this->bEnableInputPress = false;
    this->bJumpOnNavEdge = false;
    this->bJumpToWaterSurface = false;
    this->MaxInputPressTime = 1.00f;
    this->MinDistanceRate = 0.50f;
    this->FirstJumpAngle = 60.00f;
    this->JumpAngle = 60.00f;
    this->ExcutableRadius = 300.00f;
    this->ExcutableAngle = 60.00f;
    this->ExcutableAngleFromEnterFront = 360.00f;
    this->ComboJumpTarget = NULL;
    this->EnterVolume->SetupAttachment(RootComponent);
    this->ExitVolume->SetupAttachment(RootComponent);
}


