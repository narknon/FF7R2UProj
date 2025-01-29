#include "EndAnimNotifyStateBattleTargetCorrectionDistance.h"

UEndAnimNotifyStateBattleTargetCorrectionDistance::UEndAnimNotifyStateBattleTargetCorrectionDistance() {
    this->Type = EEndBattleTargetCorrectionDistanceType::TargetPosition;
    this->BaseDistance = -1.00f;
    this->SpeedLimit = -1.00f;
    this->EnableEndHitDamage = false;
    this->bEnableDirection2DInAerial = false;
    this->bEnablePCSummon = false;
}


