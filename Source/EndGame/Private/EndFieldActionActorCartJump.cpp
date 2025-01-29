#include "EndFieldActionActorCartJump.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionActorCartJump::AEndFieldActionActorCartJump(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->bAllowRailCameraSetup = true;
    this->TickVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("TickVolume"));
    this->bOnlyUsePlayer = false;
    this->bOnlyOneStep = false;
    this->TargetCartActor = NULL;
    this->bAutoEnableCartJumpArea = false;
    this->bUseParkourControl = true;
    this->AutoEnableCartJumpAreaRadius = 100.00f;
    this->AddPlayerToCartLineCheckHeight = 0.00f;
    this->bMoogleCapture00Jump = false;
    this->FirstJumpAddHeight = 0.00f;
    this->SecondJumpDeleyTime = 0.00f;
    this->SecondJumpAddHeight = 0.00f;
    this->bUseCartJumpMarker = false;
    this->bUseSecondJumpCatchPoint = false;
    this->bUseSecondJumpCatchPointIsFence = false;
    this->TickVolume->SetupAttachment(RootComponent);
}


