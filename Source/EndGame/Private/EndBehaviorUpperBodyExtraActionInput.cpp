#include "EndBehaviorUpperBodyExtraActionInput.h"

FEndBehaviorUpperBodyExtraActionInput::FEndBehaviorUpperBodyExtraActionInput() {
    this->AttachSlot = EWeaponSlot::EWeaponSlot_1;
    this->bAutoSetAttachActorDrawPause = false;
    this->bUseFullBodyBlendOnIdle = false;
    this->bShouldStopOnCompleted = false;
    this->bDisableSelfReactToBump = false;
    this->bDisableOtherReactToBump = false;
    this->bUnMovable = false;
    this->bDisableLookAt = false;
}

