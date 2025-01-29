#include "AnimNotify_EndForceFeedbackRange.h"

UAnimNotify_EndForceFeedbackRange::UAnimNotify_EndForceFeedbackRange() {
    this->Track = EEndForceFeedbackTrack::FFB_Track8;
    this->Effect = EEndForceFeedbackEffect::FFB_Effect0;
    this->bWithPriorityControl = true;
    this->bPlayForcibly = false;
    this->bContinue = false;
}


