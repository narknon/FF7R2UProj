#include "EndAnimNotifyStateBikeLaserPointer.h"

UEndAnimNotifyStateBikeLaserPointer::UEndAnimNotifyStateBikeLaserPointer() {
    this->ID = 0;
    this->EffectResourceCategory = EEndBikeLaserPointerEffectResourceCategory::Character;
    this->EffectResourceName = TEXT("FX_EN1008_Search_Laser_01");
    this->HomingDelayTime = 0.00f;
    this->HomingSpeed = 1.00f;
    this->FromCharacterType = EEndBikeLaserPointerCharacterType::Vehicle;
    this->FromSocketName = TEXT("C_Gun_Muzzle");
    this->TargetCharacterType = EEndBikeLaserPointerCharacterType::MainRider;
    this->TargetSocketName = TEXT("C_Spine_d");
}


