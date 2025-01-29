#include "EndAnimNotifyChocoboCaptureRodeo.h"

UEndAnimNotifyChocoboCaptureRodeo::UEndAnimNotifyChocoboCaptureRodeo() {
    this->PhaseNotify = EChocoboCaptureRodeoPhase::CCR_AttachStart;
    this->AttachInterpSec = 0.00f;
    this->HandType = EEndHandType::All;
}


