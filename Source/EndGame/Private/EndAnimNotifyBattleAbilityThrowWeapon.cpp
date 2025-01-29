#include "EndAnimNotifyBattleAbilityThrowWeapon.h"

UEndAnimNotifyBattleAbilityThrowWeapon::UEndAnimNotifyBattleAbilityThrowWeapon() {
    this->bAddAttackTimeThrowWeapon = false;
    this->Modifier = EEndAnimationModifierType::Overlay;
    this->Curve = EEndAnimationCurveType::OneLoop;
    this->Duration = 1.00f;
    this->BlendInTime = 0.20f;
    this->BlendOutTime = 0.20f;
}


