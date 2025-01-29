#include "EndFieldActionNavLinkActorBase.h"
#include "Components/SceneComponent.h"
#include "NavLinkCustomComponent.h"

AEndFieldActionNavLinkActorBase::AEndFieldActionNavLinkActorBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PositionComponent"));
    this->PointLinks.AddDefaulted(1);
    this->SmartLinkComp = CreateDefaultSubobject<UNavLinkCustomComponent>(TEXT("SmartLinkComp"));
}

void AEndFieldActionNavLinkActorBase::SetSmartLinkEnabled(bool bEnabled) {
}

void AEndFieldActionNavLinkActorBase::ResumePathFollowing(AActor* Agent) {
}


bool AEndFieldActionNavLinkActorBase::IsSmartLinkEnabled() const {
    return false;
}

bool AEndFieldActionNavLinkActorBase::HasMovingAgents() const {
    return false;
}


