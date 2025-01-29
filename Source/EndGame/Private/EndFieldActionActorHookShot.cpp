#include "EndFieldActionActorHookShot.h"

AEndFieldActionActorHookShot::AEndFieldActionActorHookShot(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->HitSeType = EHookShotSeType::Concrete;
}


