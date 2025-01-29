#include "EndDialogueGenerateSource.h"

FEndDialogueGenerateSource::FEndDialogueGenerateSource() {
    this->PositionPreset = NULL;
    this->bUnbindEndShotCamera = false;
    this->FirstShotCamera = EEndDialogueSequenceFirstShotCamera::Cut;
    this->EndShotCamera = EEndDialogueSequenceEndShotCamera::Cut;
    this->bReverseCamera = false;
    this->OptionalLightCount = 0;
    this->DefaultCameraGenerator = NULL;
    this->DefaultMotionGenerator = NULL;
    this->DefaultLightGenerator = NULL;
    this->NextGenerationRetryCount = 0;
}

