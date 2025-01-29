#pragma once
#include "CoreMinimal.h"
#include "EDataBaseDebugLogTypeSecondary.generated.h"

UENUM(BlueprintType)
enum class EDataBaseDebugLogTypeSecondary : uint8 {
    NONE,
    ENEMY_KILL,
    CHARACTER_LEVEL,
    PLAYER_LEVELUP,
    MATERIA_LEVELUP,
    ITEM_ADD,
    ITEM_REMOVE,
    ADD_PT_EXP,
    PCREINFORCED,
    CHANGE_EQUIP,
    PARTY_CHANGE,
    CHANGE_CHAPTER,
    ENTER_LOCATION,
    MAX,
};

