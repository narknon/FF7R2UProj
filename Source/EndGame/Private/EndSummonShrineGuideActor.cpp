#include "EndSummonShrineGuideActor.h"
#include "Components/SphereComponent.h"

AEndSummonShrineGuideActor::AEndSummonShrineGuideActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->OverlapComponent = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapComponent"));
    this->ReActivateDistance = 5000.00f;
    this->ReActivateTime = 300.00f;
    this->AIInterestPointID = TEXT("IptCmn_MStoneVision");
    this->AIInterestRadius = 1600.00f;
    this->OverlapComponent->SetupAttachment(RootComponent);
}


