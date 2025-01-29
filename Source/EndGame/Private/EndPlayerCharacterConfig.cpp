#include "EndPlayerCharacterConfig.h"

UEndPlayerCharacterConfig::UEndPlayerCharacterConfig(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->SwimmingStartDepth = -1.00f;
    this->Vault_CatchHeightMin = 220.00f;
    this->Vault_CatchHeightMax = 350.00f;
    this->Vault_SwimmingCatchHeightMin = 100.00f;
    this->Vault_SwimmingCatchHeightMax = 250.00f;
    this->MineCart_MoveFrontSpeedPerSec = 80.00f;
    this->MineCart_MoveBackSpeedPerSec = 40.00f;
    this->Climbing_CatchMaxDistance = 1000.00f;
    this->Climbing_CatchInputMaxDiffAngle = 45.00f;
    this->Climbing_CatchInputSuccessTime = 0.50f;
    this->Climbing_CatchInputSuccessTime_Dash = 0.20f;
    this->ClimbingRope_MotionPlayRate_Dash = 1.20f;
    this->FenceFrontBackNaviFallDistance = 150.00f;
    this->FenceFrontBackNaviSwimmingFallDistance = 150.00f;
    this->bZiplineUseHandIK = false;
    this->bCanFieldHoldAttack = false;
    this->bCanFieldThrowAttack = false;
    this->bCatsithRolling = false;
    this->CatsithRollingRunSpeedMin = 200.00f;
    this->CatsithRollingRunSpeedMax = 600.00f;
    this->CatsithRollingDashSpeed = 840.00f;
    this->CatsithRollingPiyoriWallSpeed = 500.00f;
    this->CatsithRollingPiyoriWallDiffAngle = 60.00f;
    this->CatsithRollingPiyoriTime = 2.50f;
    this->bWallRunning = false;
    this->RedWallStartWallContactAngle = 45.00f;
    this->bRedWallStartIsOnlyDash = false;
    this->bRedWallCanUseWallParkourJumpButton = false;
    this->RedWallLimitMoveType = EEndAnimWalkType::Run;
    this->RedWallWalkRunInputMax = 1.00f;
    this->RedWallMoveSpeedRate = 1.00f;
    this->RedWallFinishInputDownAngle = -1.00f;
    this->RedWallFinishInputDownAngleInputTime = 0.50f;
    this->RedWallGravityLimmitAngle = 1.00f;
    this->SecretEnemy_IconInputTimeMax = 2.50f;
    this->DeactiveToDodgeInputDeleyTimeForIdle = 1.00f;
    this->DeactiveToDodgeInputDeleyTimeForMove = 0.50f;
    this->BarretShootingLookAtDeactiveDistance = 500.00f;
    this->BarretShootingLookAtReactiveDistance = 600.00f;
    this->ParkourFindDirEffect = NULL;
}


