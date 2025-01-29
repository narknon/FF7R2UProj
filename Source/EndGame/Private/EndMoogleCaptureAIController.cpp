#include "EndMoogleCaptureAIController.h"

AEndMoogleCaptureAIController::AEndMoogleCaptureAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->m_TickForceOnGameThread = true;
    this->bUseDefaultBarrage = true;
    this->WonderingEQS = NULL;
    this->DistanceRemove = 3000.00f;
    this->LimitBulletNum = 60;
}

bool AEndMoogleCaptureAIController::ThrowSpawnedTrick(FVector launchOffset, FVector initvel, int32 usingidx) {
    return false;
}

bool AEndMoogleCaptureAIController::ShootBullet(FVector launchPos, FVector aimLoc) {
    return false;
}

void AEndMoogleCaptureAIController::SetAccel(FVector Accel) {
}

void AEndMoogleCaptureAIController::PlayTrickBarrageAnim(FName AnimName) {
}




bool AEndMoogleCaptureAIController::IsBarrage() const {
    return false;
}

bool AEndMoogleCaptureAIController::IsArrested() const {
    return false;
}

float AEndMoogleCaptureAIController::GetTrickParameter() const {
    return 0.0f;
}

int32 AEndMoogleCaptureAIController::GetStageClearCount() {
    return 0;
}

AEndCharacter* AEndMoogleCaptureAIController::GetOwnerMoogle() {
    return NULL;
}

int32 AEndMoogleCaptureAIController::GetCurrentStage() {
    return 0;
}

bool AEndMoogleCaptureAIController::FireBullet(FVector launchPos, FVector initvel) {
    return false;
}

void AEndMoogleCaptureAIController::BranchTrickType(EMoogleAITrickType& OutTrickType) {
}


