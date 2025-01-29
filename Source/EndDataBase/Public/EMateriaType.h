#pragma once
#include "CoreMinimal.h"
#include "EMateriaType.generated.h"

UENUM(BlueprintType)
enum class EMateriaType : uint8 {
    EMateriaType_Magic,
    EMateriaType_Help,
    EMateriaType_Command,
    EMateriaType_Independence,
    EMateriaType_Summon,
    EMateriaType_Party,
    EMateriaType_MAX UMETA(Hidden),
    EMateriaType_None = EMateriaType_MAX,
};

