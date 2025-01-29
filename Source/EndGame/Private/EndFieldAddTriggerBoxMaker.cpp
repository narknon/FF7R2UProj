#include "EndFieldAddTriggerBoxMaker.h"
#include "EndFieldActionTriggerCustomComponent.h"

UEndFieldAddTriggerBoxMaker::UEndFieldAddTriggerBoxMaker(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->TriggerBox = CreateDefaultSubobject<UEndFieldActionTriggerCustomComponent>(TEXT("AddTriggerVolume"));
}


