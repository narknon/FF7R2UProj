#include "EndWheelExpressionBoneSetting.h"

FEndWheelExpressionBoneSetting::FEndWheelExpressionBoneSetting() {
    this->bUseLocalAxisAsRightVector = false;
    this->RightVectorAxis = EAxis::None;
    this->bPerformComponentSpaceVelocityCalculation = false;
}

