#include "EndAnimalRunAIController.h"

AEndAnimalRunAIController::AEndAnimalRunAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->DefaultParameterClass = NULL;
    this->ToleranceDist2BallOnShoot = 400.00f;
    this->RadiusMerginDribble = 25.00f;
    this->RadiusMerginChase = 50.00f;
}


