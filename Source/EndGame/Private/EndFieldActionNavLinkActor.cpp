#include "EndFieldActionNavLinkActor.h"

AEndFieldActionNavLinkActor::AEndFieldActionNavLinkActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->bRefreshNavLink = false;
}


