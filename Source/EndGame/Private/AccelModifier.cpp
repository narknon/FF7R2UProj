#include "AccelModifier.h"

FAccelModifier::FAccelModifier() {
    this->MinVelocity = 0.00f;
    this->MaxVelocity = 0.00f;
    this->AccelEasingFunc = EEasingFunc::Linear;
    this->DecelEasingFunc = EEasingFunc::Linear;
    this->ModifyDuration = 0.00f;
    this->JumpEasingFunc = EEasingFunc::Linear;
    this->ModifyJumpDuration = 0.00f;
    this->CutSceneMinVelocity = 0.00f;
    this->CutSceneMaxVelocity = 0.00f;
    this->NpcMinVelocity = 0.00f;
    this->NpcMaxVelocity = 0.00f;
    this->AccelBlendExp = 0.00f;
    this->AccelSteps = 0;
    this->DecelBlendExp = 0.00f;
    this->DecelSteps = 0;
    this->ElapsedModifyTime = 0.00f;
    this->CurrentModifyAccelVelocity = 0.00f;
    this->RemainDuration = 0.00f;
    this->CachedVelocity = 0.00f;
    this->CachedElapsedModifyTime = 0.00f;
    this->JumpBlendExp = 0.00f;
    this->JumpSteps = 0;
    this->ElapsedModifyJumpTime = 0.00f;
    this->CachedBeforeJumpVelocity = 0.00f;
    this->CachedBeforeCutSceneVelocity = 0.00f;
}

