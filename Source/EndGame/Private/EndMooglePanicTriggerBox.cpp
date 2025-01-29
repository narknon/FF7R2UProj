#include "EndMooglePanicTriggerBox.h"

AEndMooglePanicTriggerBox::AEndMooglePanicTriggerBox(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->TriggerEffect = EMooglePanicTriggerType::MPT_Panic;
}


