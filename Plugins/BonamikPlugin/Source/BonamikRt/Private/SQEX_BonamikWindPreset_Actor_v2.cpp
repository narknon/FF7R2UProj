#include "SQEX_BonamikWindPreset_Actor_v2.h"
#include "Components/SceneComponent.h"

ADEPRECATED_SQEX_BonamikWindPreset_Actor_v2::ADEPRECATED_SQEX_BonamikWindPreset_Actor_v2(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
    this->m_BonamikWindCollectionAsset = NULL;
}


