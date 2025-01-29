#include "AnimNotify_EndForceFeedbackRangeAdvanced.h"

UAnimNotify_EndForceFeedbackRangeAdvanced::UAnimNotify_EndForceFeedbackRangeAdvanced() {
    this->Track = EEndForceFeedbackTrack::FFB_Track8;
    this->bWithPriorityControl = true;
    this->bPlayForcibly = false;
    this->bContinue = false;
}


