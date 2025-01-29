#include "EndAIControllerPlayerBase.h"

AEndAIControllerPlayerBase::AEndAIControllerPlayerBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bStopAILogicOnUnposses = false;
    this->MountSpawnEQS = NULL;
    this->GroundTargetReachableHeight = 300.00f;
    this->AirTargetReachableHeight = 500.00f;
    this->GroundTargetReachableHeightRangedWeapon = 3000.00f;
    this->AirTargetReachableHeightRangedWeapon = 3000.00f;
    this->ToadBattleParam = NULL;
    this->StandbyTimeMax = 2.00f;
    this->StandbyTimeMin = 1.00f;
    this->DangerDamagerSensorRadiusCoe = 1.00f;
    this->OcclusionTestSphereRadius = 20.00f;
}

void AEndAIControllerPlayerBase::TestResetAI(AEndCharacter* InCharacter) {
}

void AEndAIControllerPlayerBase::TestMoveTo(FVector TargetLocation, bool bFindPath) {
}

void AEndAIControllerPlayerBase::TestJumpToWall(AEndCharacter* InCharacter, FVector TargetLocation, FVector UpVector) {
}

void AEndAIControllerPlayerBase::TestJumpToGround(AEndCharacter* InCharacter, FTransform TargetTransform) {
}

void AEndAIControllerPlayerBase::TestAIJumpToWall(FTransform TargetTransform) {
}

void AEndAIControllerPlayerBase::TestAIJumpToGround(FTransform TargetTransform) {
}


