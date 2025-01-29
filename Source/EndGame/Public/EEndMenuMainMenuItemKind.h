#pragma once
#include "CoreMinimal.h"
#include "EEndMenuMainMenuItemKind.generated.h"

UENUM(BlueprintType)
enum class EEndMenuMainMenuItemKind : uint8 {
    ItemCraft,
    MateriaEquip,
    BattleSettings,
    BattleReport,
    EnemyReport,
    WeaponUpgrade,
    Magic,
    Item,
    Card,
    Status,
    Manual,
    SaveLoad,
    System,
    TrialSpecial,
};

