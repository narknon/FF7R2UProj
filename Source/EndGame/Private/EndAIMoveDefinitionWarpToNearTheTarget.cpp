#include "EndAIMoveDefinitionWarpToNearTheTarget.h"

UEndAIMoveDefinitionWarpToNearTheTarget::UEndAIMoveDefinitionWarpToNearTheTarget() {
    this->bLookAtTarget = true;
    this->SelectPointType = EEndAIMoveDefWarpToNearTheTargetType::NearSelf;
    this->WarpLength = 150.00f;
    this->WarpAngle = 0.00f;
}


