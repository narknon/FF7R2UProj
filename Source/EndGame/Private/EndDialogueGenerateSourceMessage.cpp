#include "EndDialogueGenerateSourceMessage.h"

FEndDialogueGenerateSourceMessage::FEndDialogueGenerateSourceMessage() {
    this->DurationMin = 0.00f;
    this->BeforeWait = 0.00f;
    this->AfterWait = 0.00f;
    this->SubtitleDelayTime = 0.00f;
    this->bIgnoreVoiceDuration = false;
    this->bAutoBindListener = false;
    this->bSuspendSequence = false;
    this->bSeamlessOutCamera = false;
    this->bRestoreToInitialPositionWhenUnbind = false;
}

