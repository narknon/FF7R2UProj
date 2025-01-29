#include "EndNaviMapStateBox.h"
#include "Components/BoxComponent.h"

AEndNaviMapStateBox::AEndNaviMapStateBox(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("NaviMapStateCollideBox"));
    this->LayerNumber = EEndNaviMapLayer::Layer_00;
    this->OpenGroupNumber = EEndNaviMapOpenGroup::OpenGroup_None;
    this->VisitGroupNumber = EEndNaviMapVisitGroup::VisitGroup_None;
    this->TargetState = EEndSceneNaviMapState::Visited;
}


