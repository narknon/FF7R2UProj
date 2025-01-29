#include "EndNavWorldLinkAttrIgnoreVolume.h"
#include "Components/SceneComponent.h"
#include "EndNavWorldLinkAttrIgnoreBoxComponent.h"

AEndNavWorldLinkAttrIgnoreVolume::AEndNavWorldLinkAttrIgnoreVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    this->EndAttrIgnoreBoxComponent = CreateDefaultSubobject<UEndNavWorldLinkAttrIgnoreBoxComponent>(TEXT("EndNavWorldLinkAttrIgnoreBoxComponent"));
    this->EndAttrIgnoreBoxComponent->SetupAttachment(RootComponent);
}


