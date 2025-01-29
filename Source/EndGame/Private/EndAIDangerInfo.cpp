#include "EndAIDangerInfo.h"

FEndAIDangerInfo::FEndAIDangerInfo() {
    this->Type = EEndAISensorDangerObjectType::DangerDamage;
    this->AttachType = EEndAISensorDangerObjectAttachType::Off;
    this->Radius = 0.00f;
    this->Length = 0.00f;
    this->bUseDodgeDirection = false;
    this->OverrideDodgeDirection = EEndAISensorDangerObjectDodgeDirectionType::Auto;
    this->bAffectedPlayer = false;
    this->bAffectedEnemy = false;
}

