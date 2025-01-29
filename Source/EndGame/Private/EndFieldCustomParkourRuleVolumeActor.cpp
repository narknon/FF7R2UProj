#include "EndFieldCustomParkourRuleVolumeActor.h"
#include "Components/SceneComponent.h"

AEndFieldCustomParkourRuleVolumeActor::AEndFieldCustomParkourRuleVolumeActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
}


