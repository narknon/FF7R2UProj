#include "EndFieldHookRopeJumpPointSetting.h"

FEndFieldHookRopeJumpPointSetting::FEndFieldHookRopeJumpPointSetting() {
    this->JumpPointType = EHookRopeJumpPointType::ToGround;
    this->HookRopeActor = NULL;
    this->ClimbingActor = NULL;
    this->GroundAttachActor = NULL;
    this->ClimbingPointIndex = 0;
    this->StartShowIconSwingAngle = 0.00f;
    this->EndShowIconSwingAngle = 0.00f;
    this->bUseShowSwingNextPointIconDistance = false;
    this->ShowSwingNextPointIconDistanceMin = 0.00f;
    this->ShowSwingNextPointIconDistanceMax = 0.00f;
    this->ShowIconDistanceMin = 0.00f;
    this->ShowIconDistanceMax = 0.00f;
    this->bShowIconGroundDistanceCheck = false;
    this->ShowIconToGroundDistance = 0.00f;
    this->bRayCheckPlayerToJumpPoint = false;
    this->bRayCheckHookPointToJumpPoint = false;
}

