#include "End3DAudioActor.h"
#include "Components/SceneComponent.h"

AEnd3DAudioActor::AEnd3DAudioActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
    this->_autoPlayDist = 5000.00f;
    this->_useType = EEnd3DAudioActorUseType::JukeBox;
    this->_overwriteAttenuationSetting = NULL;
}


