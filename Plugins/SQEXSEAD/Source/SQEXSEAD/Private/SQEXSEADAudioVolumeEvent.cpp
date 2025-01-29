#include "SQEXSEADAudioVolumeEvent.h"

FSQEXSEADAudioVolumeEvent::FSQEXSEADAudioVolumeEvent() {
    this->Command = ESQEXSEADAudioVolumeCommand::None;
    this->ExteriorAudioVolumeSoundOcclusionVolume = 0.00f;
    this->ExteriorAudioVolumeSoundOcclusionLPF = 0.00f;
    this->ObstructionVolume = 0.00f;
    this->ObstructionLPF = 0.00f;
    this->FadeTime = 0.00f;
}

