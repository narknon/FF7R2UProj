#include "EndBTDecorator_IsInActiveRecognitionVolume.h"

UEndBTDecorator_IsInActiveRecognitionVolume::UEndBTDecorator_IsInActiveRecognitionVolume() {
    this->NodeName = TEXT("[End][AIPC]IsInActiveRecognitionVolume");
    this->Type = EEndAIRecognitionVolumeType::SafeArea;
}


