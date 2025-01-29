#include "EndBattleAISU2050BaseController.h"

AEndBattleAISU2050BaseController::AEndBattleAISU2050BaseController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->EXModeTime = 30.00f;
    this->PathFindHeight = 600.00f;
}

void AEndBattleAISU2050BaseController::SetBattleMode(EEndBattleNeoBahaBattleMode BattleMode) {
}

void AEndBattleAISU2050BaseController::OnChangeToBoosterMode() {
}

void AEndBattleAISU2050BaseController::OnChangeToBladeMode() {
}

EEndBattleNeoBahaBattleMode AEndBattleAISU2050BaseController::GetCurrentBattleMode() {
    return EEndBattleNeoBahaBattleMode::Normal;
}

bool AEndBattleAISU2050BaseController::ChangeBattleMode(EEndBattleNeoBahaBattleMode nextBattleMode, bool swapAbility) {
    return false;
}


