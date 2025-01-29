#include "EndFieldForceParkourSetting.h"

FEndFieldForceParkourSetting::FEndFieldForceParkourSetting() {
    this->SetType = EForceParkourSetType::NaviEdgeArea;
    this->JumpType = EForceParkourJumpType::Default;
    this->CheckType = EForceParkourCheckType::Default;
    this->AddtiveJumpHeight = 0.00f;
    this->bLandFaildToSafeTeleport = false;
}

