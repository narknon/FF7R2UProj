#include "EndDataTableEnemyTerritory.h"

FEndDataTableEnemyTerritory::FEndDataTableEnemyTerritory() {
    this->UniqueIndex = 0;
    this->TerritoryType = 0;
    this->RespawnTimer = 0.00f;
    this->SaveTerritoryState = 0;
    this->ForceRepopWhenSavedOverTerritory = 0;
    this->HideNavimap = 0;
    this->RestartConsecutiveBattles = 0;
    this->IgnoreSafeEscapeVolumes = 0;
    this->ForceEnemyDynamicBattleAreaSizeMax = 0;
    this->SetDisableReserveMemberCommand = 0;
    this->DontForceKillHiddenWaveEnemiesOnKillTerritoryEnemies = 0;
    this->WinFieldTransitionMotionAllowFreeCamera = 0;
}

