#include "EndWallNavAreaVolume.h"
#include "Components/SceneComponent.h"
#include "EndWallNavBoxComponent.h"

AEndWallNavAreaVolume::AEndWallNavAreaVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    this->EndWallNavBox = CreateDefaultSubobject<UEndWallNavBoxComponent>(TEXT("EndWallNavBox"));
    this->EndWallNavBox->SetupAttachment(RootComponent);
}


