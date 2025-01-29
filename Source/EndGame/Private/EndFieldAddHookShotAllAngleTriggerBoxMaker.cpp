#include "EndFieldAddHookShotAllAngleTriggerBoxMaker.h"
#include "EndFieldActionTriggerCustomComponent.h"

UEndFieldAddHookShotAllAngleTriggerBoxMaker::UEndFieldAddHookShotAllAngleTriggerBoxMaker(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->TriggerBox = CreateDefaultSubobject<UEndFieldActionTriggerCustomComponent>(TEXT("AddAllAngleTriggerVolume"));
}


