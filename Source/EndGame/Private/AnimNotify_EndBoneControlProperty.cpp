#include "AnimNotify_EndBoneControlProperty.h"

FAnimNotify_EndBoneControlProperty::FAnimNotify_EndBoneControlProperty() {
    this->Bone = EEndControlBone::Hip;
    this->ControlType = EEndControlBoneType::None;
    this->Condition = EEndControlBoneCondition::None;
}

