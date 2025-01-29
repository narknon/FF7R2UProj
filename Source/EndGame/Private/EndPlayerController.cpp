#include "EndPlayerController.h"

AEndPlayerController::AEndPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->ClickEventKeys.AddDefaulted(1);
    this->PlayerExistNavAreaComponent = NULL;
    this->PlayerLeaderActionParamComponent = NULL;
    this->LeaderCharacter = NULL;
    this->BattleTalkOnEndBattleClass = NULL;
    this->BattleTalkOnEndBattle = NULL;
    this->ActiveVehicleCoordinator = NULL;
    this->PlayerTrigger = NULL;
    this->MaxMouseSensitivity = 2.00f;
    this->MinMouseSensitivity = 0.10f;
}


