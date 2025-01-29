#include "EndFieldActionActorBase.h"

AEndFieldActionActorBase::AEndFieldActionActorBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->ForceActiveTargetIcon = false;
    this->WaitReservation = false;
}


