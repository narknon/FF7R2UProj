#include "AnimNotifyState_EndAIBattleDangerObject.h"

UAnimNotifyState_EndAIBattleDangerObject::UAnimNotifyState_EndAIBattleDangerObject() {
    this->bMultipleCreate = false;
    this->bReferencedByDamageSource = false;
    this->Radius = 300.00f;
    this->Length = 0.00f;
    this->DodgeDirection = EEndAISensorDangerObjectDodgeDirectionType::Auto;
    this->bUseDodgeDirection = false;
    this->DestroyDelayTime = 0.00f;
    this->bUseDestroyDelayTime = false;
    this->bAffectedPlayer = true;
    this->bAffectedEnemy = false;
    this->GraphicsMode = EEndAISensorDangerObjectGraphicsMode::All;
}


