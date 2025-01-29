#include "AnimNotify_MoveActorTimeline.h"

UAnimNotify_MoveActorTimeline::UAnimNotify_MoveActorTimeline() {
    this->bDisplayDebugMovement = false;
    this->bDisplayDebugRotation = false;
    this->bAutoTangents = false;
    this->CurrentTime = 0.00f;
    this->StartTime = 0.00f;
    this->EndTime = 0.00f;
    this->TotalTime = 0.00f;
    this->SplineComp = NULL;
    this->MovingComponent = NULL;
}


