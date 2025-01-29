#include "EndFieldActionRedChainDoorActor.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionRedChainDoorActor::AEndFieldActionRedChainDoorActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->InvisibleRopeObjectClass = NULL;
    this->TickVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("TickVolume"));
    this->LowerChainMeshActor = NULL;
    this->UpperChainMeshActor = NULL;
    this->DoorMeshActor = NULL;
    this->StretchPoleMeshActor = NULL;
    this->bDropToReverseChain = false;
    this->bReverseChainStretchMaxToFix = false;
    this->bUseChainMoveAngleLimit = false;
    this->ChainMoveAngleLimit = 45.00f;
    this->DoorOpenHeight = 1000.00f;
    this->StrethcPoleMoveStartPos = 0.00f;
    this->StrethcPoleMoveStopPos = 1500.00f;
    this->ChainMoveMoveType = EEndSpecificMoveType::Walk;
    this->GoalIconName = TEXT("GoalIcon_Default__EndFieldActionRedChainDoorActor");
    this->ChainDistanceLimit = -1.00f;
    this->TickVolume->SetupAttachment(RootComponent);
}


