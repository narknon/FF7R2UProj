#include "EndInterestPoint.h"
#include "Components/SceneComponent.h"

AEndInterestPoint::AEndInterestPoint(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    this->Type = EEndInterestPointReactionActorType::Npc;
    this->InterestRadius = 300.00f;
    this->InterestTemplateID = EEndInterestPointTemplate::Template00;
    this->IsForcedRecognition = false;
}


