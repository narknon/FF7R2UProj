#include "EndDialogueCommandSection.h"

UEndDialogueCommandSection::UEndDialogueCommandSection() {
    this->CommandType = 0;
    this->bUnbindCamera = false;
    this->bSeamlessOutCamera = false;
    this->bSuspendSequence = false;
    this->bRestoreToInitialPositionWhenUnbind = true;
}


