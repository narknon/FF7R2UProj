#include "EndWheeledVehicleSplineMoveActor.h"

AEndWheeledVehicleSplineMoveActor::AEndWheeledVehicleSplineMoveActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bSetTransformOnStart = false;
    this->bSetSpeedOnStart = false;
    this->SpeedOnStartKph = 0.00f;
}


