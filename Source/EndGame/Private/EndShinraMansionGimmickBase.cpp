#include "EndShinraMansionGimmickBase.h"
#include "Components/SceneComponent.h"

AEndShinraMansionGimmickBase::AEndShinraMansionGimmickBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}


