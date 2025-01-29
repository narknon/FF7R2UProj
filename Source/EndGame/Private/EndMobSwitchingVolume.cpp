#include "EndMobSwitchingVolume.h"
#include "Components/SceneComponent.h"

AEndMobSwitchingVolume::AEndMobSwitchingVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    this->bOverrideAiMoveType = false;
    this->OverrideAiMoveType = EEndAiMoveType::RUN;
    this->bOverrideMoveDirectionType = false;
    this->OverrideMoveDirectionType = EEndMobMoveDirectionType::Plus;
    this->bBindToMobPrefab = false;
    this->MobPrefabClass = NULL;
    this->bStopBeforeBind = false;
    this->bLookAt = false;
    this->bSetLocationWork = false;
    this->LocationWorkValue = 0;
}


