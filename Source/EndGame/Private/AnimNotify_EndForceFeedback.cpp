#include "AnimNotify_EndForceFeedback.h"

UAnimNotify_EndForceFeedback::UAnimNotify_EndForceFeedback() {
    this->Track = EEndForceFeedbackTrack::FFB_Track8;
    this->Effect = EEndForceFeedbackEffect::FFB_Effect0;
    this->bWithPriorityControl = true;
    this->bPlayForcibly = false;
}


