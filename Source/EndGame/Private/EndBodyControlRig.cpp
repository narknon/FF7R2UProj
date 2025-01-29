#include "EndBodyControlRig.h"

UEndBodyControlRig::UEndBodyControlRig() {
    this->CenterBoneName = TEXT("C_Hip_a");
    this->HeadBoneName = TEXT("C_Head_a");
    this->LookAtTargetBoneName = TEXT("C_Head_a");
    this->AIWalkRotationRateScale = 1.00f;
    this->AIRunRotationRateScale = 1.00f;
    this->AIDashRotationRateScale = 1.00f;
}


