#include "EndBattleAreaActor.h"
#include "Components/SceneComponent.h"
#include "EndBattleAreaBoxComponent.h"
#include "EndCationAreaBoxComponent.h"
#include "EndNavModifierComponent.h"

AEndBattleAreaActor::AEndBattleAreaActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    this->EndBattleAreaBoxComponent = CreateDefaultSubobject<UEndBattleAreaBoxComponent>(TEXT("EndBattleAreaBoxComponent"));
    this->EndCationAreaBoxComponent = CreateDefaultSubobject<UEndCationAreaBoxComponent>(TEXT("EndCationAreaBoxComponent"));
    this->BattleModifierVolume = CreateDefaultSubobject<UEndNavModifierComponent>(TEXT("BattleModifier"));
    this->CationModifierVolume = CreateDefaultSubobject<UEndNavModifierComponent>(TEXT("CationModifier"));
    this->ExtendedBattleModifierVolume = CreateDefaultSubobject<UEndNavModifierComponent>(TEXT("ExtendedModifier"));
    this->EndBattleAreaBoxComponent->SetupAttachment(RootComponent);
    this->EndCationAreaBoxComponent->SetupAttachment(RootComponent);
}


