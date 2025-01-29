#include "EndBikeTriggerBox.h"

AEndBikeTriggerBox::AEndBikeTriggerBox(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->Type = EEndBikeTriggerBoxType::Destroy;
}

void AEndBikeTriggerBox::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor) {
}

void AEndBikeTriggerBox::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor) {
}


