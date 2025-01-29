#include "EndNavMultiSwitchingVolume.h"
#include "Components/SceneComponent.h"
#include "EndMultiBoxComponent.h"
#include "EndNavModifierComponent.h"

AEndNavMultiSwitchingVolume::AEndNavMultiSwitchingVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    this->IsFirstStart = true;
    this->CollisionProfileType = ECollisionProfileType::Wall;
    this->CollisionAndNavProfileType = ECollisionAndNavProfileType::Wall;
    this->bPC_Wall = true;
    this->bParty_Wall = true;
    this->bSubParty_Wall = true;
    this->bNPC_Wall = true;
    this->bEnemy_Wall = true;
    this->ExtraOption = ECollisionProfileExtraOption::Default;
    this->NavAreaType = EEndNavAreaType::Impassable;
    this->EndMultiBoxComponent = CreateDefaultSubobject<UEndMultiBoxComponent>(TEXT("EndMultiBoxComponent"));
    this->ModifierVolume = CreateDefaultSubobject<UEndNavModifierComponent>(TEXT("Modifier"));
    this->EndMultiBoxComponent->SetupAttachment(RootComponent);
}


