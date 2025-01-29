#include "EndVehicleRestrictedAreaSplineCollisionActor.h"
#include "EndVehicleRestrictedAreaWallCollisionComponent.h"

AEndVehicleRestrictedAreaSplineCollisionActor::AEndVehicleRestrictedAreaSplineCollisionActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->WallCollisionComponent = CreateDefaultSubobject<UEndVehicleRestrictedAreaWallCollisionComponent>(TEXT("WallCollisionComponent"));
    this->bUseAsCollisionWallOnly = false;
    this->bUseSplineCurveAuto = false;
    this->WallCollisionComponent->SetupAttachment(RootComponent);
}


