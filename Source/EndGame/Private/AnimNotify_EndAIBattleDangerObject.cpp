#include "AnimNotify_EndAIBattleDangerObject.h"

UAnimNotify_EndAIBattleDangerObject::UAnimNotify_EndAIBattleDangerObject() {
    this->bMultipleCreate = false;
    this->bReferencedByDamageSource = false;
    this->Duration = 0.00f;
    this->Radius = 300.00f;
    this->Length = 0.00f;
    this->DodgeDirection = EEndAISensorDangerObjectDodgeDirectionType::Auto;
    this->bUseDodgeDirection = false;
    this->bAffectedPlayer = true;
    this->bAffectedEnemy = false;
    this->GraphicsMode = EEndAISensorDangerObjectGraphicsMode::All;
}


