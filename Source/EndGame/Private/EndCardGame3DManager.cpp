#include "EndCardGame3DManager.h"

AEndCardGame3DManager::AEndCardGame3DManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->BattleCameraId = -1;
    this->CardGameBoard = NULL;
    this->CardBoardClass = NULL;
    this->CardHandClass = NULL;
    this->CardPlacementActor = NULL;
    this->FlagPlayerClass = NULL;
    this->FlagOpponentClass = NULL;
    this->bFlagPlayerTurnAnim = false;
    this->bFlagOpponentTurnAnim = false;
    this->TokenPlayerClass = NULL;
    this->TokenEnemyClass = NULL;
    this->bEnemyTurnVisible = false;
    this->bPlayerTurnVisible = false;
    this->bDamageWinVisible = false;
    this->bDamageWin2Visible = false;
}

void AEndCardGame3DManager::OnFinishBattleCamera() {
}


