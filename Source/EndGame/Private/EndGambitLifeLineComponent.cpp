#include "EndGambitLifeLineComponent.h"

UEndGambitLifeLineComponent::UEndGambitLifeLineComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RecoverIntervalSec = 10.00f;
    this->bRootLife = false;
}


