#include "EndBattleAISU0001BaseController.h"

AEndBattleAISU0001BaseController::AEndBattleAISU0001BaseController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->MoogleBombHoldingStartAnimation = TEXT("B_AtkBomb01_0");
    this->MoogleBombHoldingIdleAnimation = TEXT("B_AtkBomb01_1");
}

void AEndBattleAISU0001BaseController::SetMoogleBombHidden(bool IsHidden) {
}


