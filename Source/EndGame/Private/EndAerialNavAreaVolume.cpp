#include "EndAerialNavAreaVolume.h"
#include "Components/SceneComponent.h"
#include "EndAerialNavBoxComponent.h"

AEndAerialNavAreaVolume::AEndAerialNavAreaVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    this->EndArealNavBox = CreateDefaultSubobject<UEndAerialNavBoxComponent>(TEXT("EndAerialNavBox"));
    this->EndArealNavBox->SetupAttachment(RootComponent);
}


