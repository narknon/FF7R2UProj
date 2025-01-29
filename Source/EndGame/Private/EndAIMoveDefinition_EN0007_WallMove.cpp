#include "EndAIMoveDefinition_EN0007_WallMove.h"

UEndAIMoveDefinition_EN0007_WallMove::UEndAIMoveDefinition_EN0007_WallMove() {
    this->bNotActionInterrupt = true;
    this->bNotReactionAction = true;
    this->DistanceMin = 1300.00f;
    this->DistanceMax = 2500.00f;
    this->Height = 350.00f;
    this->AddDistance = 300.00f;
    this->AdjustTime = 1.00f;
    this->WallMoveRotationRateScale = 0.06f;
    this->WallMoveRotationRateScaleDelay = 0.00f;
    this->AutoFitUpVectorRotationSpeed = 720.00f;
    this->bDrawDebug = false;
}


