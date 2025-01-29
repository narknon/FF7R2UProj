#include "EndCharacterAttachEffectArguments.h"

FEndCharacterAttachEffectArguments::FEndCharacterAttachEffectArguments() {
    this->ResourceCategory = EEndCharacterAttachEffectResourceCategoryType::Resident;
    this->ResourceChara = NULL;
    this->bRemoveOnEscape = false;
    this->bRemoveOnDeath = false;
    this->bDetachOnRemove = false;
    this->BeamTargetChara = NULL;
    this->bBeamTargetDisableContactTargetChara = false;
    this->bBeamTargetContactWall = false;
    this->bBeamTargetContactOwnerChara = false;
    this->bLineEffect = false;
    this->LineEffectTangentLength = 0.00f;
    this->CreateSecondMin = 0.00f;
    this->CreateSecondMax = 0.00f;
    this->LoopOffSecondMin = 0.00f;
    this->LoopOffSecondMax = 0.00f;
    this->ReCreateSecondMin = 0.00f;
    this->ReCreateSecondMax = 0.00f;
    this->bSynchroParentActorVisible = false;
}

