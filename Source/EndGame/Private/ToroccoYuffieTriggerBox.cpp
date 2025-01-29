#include "ToroccoYuffieTriggerBox.h"

AToroccoYuffieTriggerBox::AToroccoYuffieTriggerBox(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->TargetBox = NULL;
    this->TotalTime = 0.00f;
    this->Tolerance_MinimumPassTime = 0.10f;
    this->MinimumPassTime = 0.00f;
    this->MaximumPassTime = 0.00f;
}


