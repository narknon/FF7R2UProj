#include "EndNavModifierLockOnSiteVolume.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "EndNavModifierComponent.h"

AEndNavModifierLockOnSiteVolume::AEndNavModifierLockOnSiteVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    this->ResponseAreaID = TEXT("rpaLockOnMode");
    this->ResponseAreaPlayerID = TEXT("rpaLockOnModePlayer");
    this->RangeComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RangeComponent"));
    this->TargetIconComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TargetIconComponent"));
    this->ModifierVolume = CreateDefaultSubobject<UEndNavModifierComponent>(TEXT("Modifier"));
    this->RangeComponent->SetupAttachment(RootComponent);
    this->TargetIconComponent->SetupAttachment(RootComponent);
}


