#include "EndDataTablePlannerEvent.h"

FEndDataTablePlannerEvent::FEndDataTablePlannerEvent() {
    this->Time = 0.00f;
    this->MinSubtitleTime = 0.00f;
    this->TimeAfterVoice = 0.00f;
    this->OutputType = 0;
    this->CanSkip = 0;
    this->NoLipSync = 0;
    this->HideSubtitle = 0;
    this->VoiceType = 0;
    this->VoicePackCategory = 0;
    this->CameraType = 0;
    this->TalkerCmd = 0;
    this->AttenuationOverride = 0;
    this->DisallowTalkIDOverwrite = 0;
}

