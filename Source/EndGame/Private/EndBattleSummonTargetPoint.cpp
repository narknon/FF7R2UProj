#include "EndBattleSummonTargetPoint.h"

AEndBattleSummonTargetPoint::AEndBattleSummonTargetPoint(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bSpawn_All = true;
    this->bSpawn_Ifrit = false;
    this->bSpawn_Chocobo = false;
    this->bSpawn_Shiva = false;
    this->bSpawn_Leviathan = false;
    this->bSpawn_Bahamut = false;
    this->bSpawn_DebuChoco = false;
    this->bSpawn_Carbuncle = false;
    this->bSpawn_Sabotender = false;
    this->bSpawn_BabyChocobo = false;
    this->bSpawn_Ramuh = false;
    this->bSpawn_Titan = false;
    this->bSpawn_Odin = false;
    this->bSpawn_Kjata = false;
    this->bSpawn_Alexander = false;
    this->bSpawn_Phoenix = false;
    this->bSpawn_NeoBahamut = false;
    this->bSpawn_Gilgamesh = false;
    this->bSpawn_Magicpot = false;
    this->bSpawn_End2Hinachocobo = false;
    this->bSpawn_DLCMoogle = false;
    this->bWarp_All = true;
    this->bWarp_Ifrit = false;
    this->bWarp_Chocobo = false;
    this->bWarp_Shiva = false;
    this->bWarp_Leviathan = false;
    this->bWarp_Bahamut = false;
    this->bWarp_DebuChoco = false;
    this->bWarp_Carbuncle = false;
    this->bWarp_Sabotender = false;
    this->bWarp_BabyChocobo = false;
    this->bWarp_Ramuh = false;
    this->bWarp_Titan = false;
    this->bWarp_Odin = false;
    this->bWarp_Kjata = false;
    this->bWarp_Alexander = false;
    this->bWarp_Phoenix = false;
    this->bWarp_NeoBahamut = false;
    this->bWarp_Gilgamesh = false;
    this->bWarp_Magicpot = false;
    this->bWarp_End2Hinachocobo = false;
    this->bWarp_DLCMoogle = false;
    this->bCutScene = true;
    this->bResetLocation = false;
    this->bOmen = false;
    this->bLevelCutScene = false;
    this->bFreeze = true;
    this->PointPriority = ESummonPointPriority::Normal;
    this->LocalNumber = -1;
    this->bAppearPointTheGround = false;
    this->bGroundFailuer = false;
}


