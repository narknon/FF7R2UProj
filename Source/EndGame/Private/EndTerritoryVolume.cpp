#include "EndTerritoryVolume.h"
#include "EndAerialNavBoxComponent.h"
#include "EndNavAreaTerritory.h"

AEndTerritoryVolume::AEndTerritoryVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->AreaClass = UEndNavAreaTerritory::StaticClass();
    this->bIgnoreTerritoryExtendedAreaForAerialPath = false;
    this->CreateAerialHeight = 550.00f;
    this->bCreateAerialPpint = true;
    this->AerialNavBox = CreateDefaultSubobject<UEndAerialNavBoxComponent>(TEXT("UEndAerialNavBoxComponent"));
    this->EnemyTerritoryFreeBattleAreaSize = 1000.00f;
    this->AerialNavBox->SetupAttachment(RootComponent);
}


