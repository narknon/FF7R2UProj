#include "EndAIActionDefinition.h"

UEndAIActionDefinition::UEndAIActionDefinition() {
    this->FirstActWaitTime = 0.00f;
    this->CoolTime = 0.00f;
    this->CoolTimeWidth = 0.00f;
    this->NotMoveTime = 0.00f;
    this->ActionAfterInterval = 0.00f;
    this->MoveTimeOut = 0.00f;
    this->bCanInterrupt = false;
    this->bSuspendCounter = false;
    this->bNotPreCanActionCancel = false;
    this->bIgnoreTargetToMoveCancel = false;
    this->bCheckLineTrace = false;
    this->bCanSyncAction = false;
    this->bIgnoreDummyBattle = false;
    this->bIgnoreGuestChara = false;
    this->bIgnoreTargetChara = true;
    this->TrialCount = -1;
    this->TrialStraightCount = -1;
    this->TrialStraightCountCategory = EEndAIActionTrialStraightCountCategory::None;
    this->bUseDistance = false;
    this->DistanceMin = 0.00f;
    this->DistanceMax = 0.00f;
    this->bUseHeight = false;
    this->HeightMin = 0.00f;
    this->HeightMax = 0.00f;
    this->bUseAngleYaw = false;
    this->AngleYaw = 45.00f;
    this->AngleYawOffset = 0.00f;
    this->bUseAnglePitch = false;
    this->AnglePitch = 45.00f;
    this->AnglePitchOffset = 0.00f;
    this->FlyingHeight = 0.00f;
    this->bDebugDisableLog = false;
    this->bDebugLog = false;
}


