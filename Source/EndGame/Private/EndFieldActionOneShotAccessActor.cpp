#include "EndFieldActionOneShotAccessActor.h"
#include "EndFieldActionTriggerComponent.h"

AEndFieldActionOneShotAccessActor::AEndFieldActionOneShotAccessActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->PointLinks.AddDefaulted(1);
    this->TikableVolume = CreateDefaultSubobject<UEndFieldActionTriggerComponent>(TEXT("TikableVolume"));
    this->GunSkeletalMeshClass = NULL;
    this->GunSkeletalMeshActorClass = NULL;
    this->IconInputSuccessTime = 0.00f;
    this->bLongInputStartAndPlayAnimation = false;
    this->bCanNormalCompleteToReWind = false;
    this->bEnablePlayerAttachInterp = true;
    this->bKeepCompleteAnimation = false;
    this->bPlayerWaitAccessTargetStartAnimation = false;
    this->bUseSuccessAnimation = false;
    this->bUseCancelAnimation = false;
    this->bLifeSpot = false;
    this->bTower = false;
    this->TikableVolume->SetupAttachment(RootComponent);
}


