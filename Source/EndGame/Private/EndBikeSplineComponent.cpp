#include "EndBikeSplineComponent.h"

UEndBikeSplineComponent::UEndBikeSplineComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->EnemySlideMoveLimitWidth = 0.00f;
    this->BuggyMaxSlideLength = 0.00f;
    this->BuggyEnableInputSlideLength = 0.00f;
    this->BuggyNoHitSlideLengthBySpecifyPlayerMoveLine = 0.00f;
}


