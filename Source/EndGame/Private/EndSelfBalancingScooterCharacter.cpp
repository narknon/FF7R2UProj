#include "EndSelfBalancingScooterCharacter.h"

AEndSelfBalancingScooterCharacter::AEndSelfBalancingScooterCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->MovementSetting = NULL;
    this->ScooterColor = EScooterColor::RedScooter;
    this->RiderActor = NULL;
}


