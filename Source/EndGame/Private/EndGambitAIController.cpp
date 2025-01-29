#include "EndGambitAIController.h"

AEndGambitAIController::AEndGambitAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->m_GeneratedLaneIdx = 0;
    this->bAltAbility = false;
}

void AEndGambitAIController::SetGroundMode() {
}

void AEndGambitAIController::SetDisableLastActionFooter(bool bDisable) {
}




int32 AEndGambitAIController::GetStageIndex() const {
    return 0;
}

AEndCharacter* AEndGambitAIController::GetOwnerUnit() {
    return NULL;
}

FName AEndGambitAIController::GetLastAction() const {
    return NAME_None;
}

TArray<AEndCharacter*> AEndGambitAIController::GetLaneUnits(EGambitTargetLaneType Lanetype, bool bOpposing) {
    return TArray<AEndCharacter*>();
}

uint8 AEndGambitAIController::GetGeneratedLaneIdx() const {
    return 0;
}

void AEndGambitAIController::DeleteAttribute() {
}

void AEndGambitAIController::AddLastGambitActionRemain() {
}


