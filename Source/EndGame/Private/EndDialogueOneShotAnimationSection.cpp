#include "EndDialogueOneShotAnimationSection.h"

UEndDialogueOneShotAnimationSection::UEndDialogueOneShotAnimationSection() {
    this->AnimSequence = NULL;
    this->BlendTime = 0.00f;
    const FProperty* p_StartTime = GetClass()->FindPropertyByName("StartTime");
    (*p_StartTime->ContainerPtrToValuePtr<float>(this)) = 0.00f;
    this->UpperBodyAnimSequence = NULL;
    this->UpperBodyBlendTime = 0.00f;
    this->UpperBodyDelayTime = 0.00f;
}


