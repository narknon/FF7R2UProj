#pragma once
#include "CoreMinimal.h"
#include "EEndExtensionAIStateBattleEvacuation.generated.h"

UENUM(BlueprintType)
enum class EEndExtensionAIStateBattleEvacuation : uint8 {
    NONE,
    FIELD_MODE,
    BATTLE_MODE,
    BUGEN_HAGEN = 16,
    BUGEN_HAGEN_RETURN,
};

