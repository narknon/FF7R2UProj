#include "EndAnimNotifyStateBattleTargetCorrectionDirection.h"

UEndAnimNotifyStateBattleTargetCorrectionDirection::UEndAnimNotifyStateBattleTargetCorrectionDirection() {
    this->Type = EEndBattleTargetCorrectionDirectionType::TargetPosition;
    this->Pitch = false;
    this->ForwardBasicAngle = 0.00f;
    this->Angle = -1.00f;
    this->EachAngle = false;
    this->AngleLeft = -1.00f;
    this->AngleRight = -1.00f;
    this->EnableEndHitDamage = false;
    this->EnableEndTargetOutsideAngle = false;
    this->EndTargetOutsideAngle = 0.00f;
    this->EnableEndCorrectionNeedless = false;
}


