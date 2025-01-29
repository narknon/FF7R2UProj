#include "EndBTDecorator_CheckDistance.h"

UEndBTDecorator_CheckDistance::UEndBTDecorator_CheckDistance() {
    this->Operator = EEndAiMathCmp::Equal;
    this->bUseDistanceBB = false;
    this->CheckDistance = 0.00f;
    this->bUseOffsetBB = false;
    this->CheckDistanceOffset = 0.00f;
    this->DistanceType = EEndAIDistanceType::Dist3D;
    this->UseBodyRadius_From = false;
    this->UseBodyRadius_To = false;
    this->bClampZero = false;
}


