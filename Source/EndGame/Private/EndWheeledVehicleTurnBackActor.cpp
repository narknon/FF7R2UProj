#include "EndWheeledVehicleTurnBackActor.h"
#include "Components/SceneComponent.h"

AEndWheeledVehicleTurnBackActor::AEndWheeledVehicleTurnBackActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    this->ForwardSpeedKph = 60.00f;
    this->BackwardSpeedKph = 40.00f;
    this->ApplyMaxSteeringUntilLessDeltaAngle = 30.00f;
    this->FinishDeltaAngle = 5.00f;
    this->MinMoveLength = 300.00f;
    this->MinMoveLengthIfMoveForwardOnly = 900.00f;
    this->Timelimit = 5.00f;
    this->MovesBackOnceXDirParam0 = 300.00f;
    this->MovesBackOnceXDirParam1 = 150.00f;
    this->MovesBackOnceXDirParam2 = 300.00f;
}


