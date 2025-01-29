#include "AnimNotify_EndForceFeedbackAdvanced.h"

UAnimNotify_EndForceFeedbackAdvanced::UAnimNotify_EndForceFeedbackAdvanced() {
    this->Track = EEndForceFeedbackTrack::FFB_Track8;
    this->bWithPriorityControl = true;
    this->bPlayForcibly = false;
}


