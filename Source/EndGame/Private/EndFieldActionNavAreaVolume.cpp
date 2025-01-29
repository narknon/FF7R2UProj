#include "EndFieldActionNavAreaVolume.h"
#include "EndNavAreaFieldAction.h"

UEndFieldActionNavAreaVolume::UEndFieldActionNavAreaVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->AreaClass = UEndNavAreaFieldAction::StaticClass();
}


