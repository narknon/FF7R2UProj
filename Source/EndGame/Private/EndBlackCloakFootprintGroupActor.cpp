#include "EndBlackCloakFootprintGroupActor.h"
#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"

AEndBlackCloakFootprintGroupActor::AEndBlackCloakFootprintGroupActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
    this->_SpawnType = BlackCloakFootprintCreationType::Auto;
    this->FootPrintBaseComponent = CreateDefaultSubobject<USplineComponent>(TEXT("CameraRailComponent"));
    this->_HorizontalDistBetweenFootPrints = 50.00f;
    this->_VerticalDistBetweenFootPrints = 50.00f;
    this->_FootPrintsAngle = 15.00f;
    this->FootPrintBaseComponent->SetupAttachment(RootComponent);
}


