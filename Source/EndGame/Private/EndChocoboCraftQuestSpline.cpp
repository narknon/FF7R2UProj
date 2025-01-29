#include "EndChocoboCraftQuestSpline.h"

AEndChocoboCraftQuestSpline::AEndChocoboCraftQuestSpline(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->DistanceBetweenFirstPoints = 0.00f;
    this->HeightRequiredOnAdjustedPoint = 0.00f;
    this->bUpdateEndAndStartPoints = false;
    this->bSimulateWave = false;
}


