#include "EndAnimNotifyBattleAbilityRushWeapon.h"

UEndAnimNotifyBattleAbilityRushWeapon::UEndAnimNotifyBattleAbilityRushWeapon() {
    this->RushGroundWeaponOffsetZ = 0.00f;
    this->RushTime = 0.00f;
    this->RushCactuarWeaponPitch = 0.00f;
    this->Modifier = EEndAnimationModifierType::Overlay;
    this->Curve = EEndAnimationCurveType::OneLoop;
    this->Duration = 1.00f;
    this->BlendInTime = 0.20f;
    this->BlendOutTime = 0.20f;
}


