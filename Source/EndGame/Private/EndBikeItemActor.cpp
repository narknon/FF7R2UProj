#include "EndBikeItemActor.h"
#include "EndShapeComponent.h"

AEndBikeItemActor::AEndBikeItemActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->AddATBGaugeRate = 0.00f;
    this->AddATBGaugeTime = 5.00f;
    this->bScoreItem = false;
    this->bEngineBoostItem = false;
    this->OverlapCollisionComponent = CreateDefaultSubobject<UEndShapeComponent>(TEXT("OverlapComponent"));
    this->OverlapCollisionComponent->SetupAttachment(RootComponent);
}


