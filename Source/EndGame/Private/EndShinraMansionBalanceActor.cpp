#include "EndShinraMansionBalanceActor.h"

AEndShinraMansionBalanceActor::AEndShinraMansionBalanceActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->BalanceLiftPillar = NULL;
    this->DoorOpenTriggerBox = NULL;
    this->BalanceLiftLeft = NULL;
    this->LeftDefaultWeight = 0.00f;
    this->BalanceLiftRightBox = NULL;
    this->BalanceLiftRight = NULL;
    this->RightDefaultWeight = 0.00f;
    this->BalanceLiftLeftBox = NULL;
    this->MaxWeight = 10.00f;
    this->MaxLiftZ = 0.00f;
    this->MinLiftZ = 0.00f;
    this->DesireBalanceRate = 0.50f;
    this->CurrentBalanceRate = 0.50f;
    this->LiftOffset = 0.00f;
    this->IncludeCharacterMass = true;
    this->WeightOnRightLift = 0.00f;
    this->WeightOnLeftLift = 0.00f;
    this->_TriggerIntervalRight = 1.00f;
    this->_TriggerIntervalLeft = 1.00f;
}


