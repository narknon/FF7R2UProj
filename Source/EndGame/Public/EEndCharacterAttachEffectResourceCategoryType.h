#pragma once
#include "CoreMinimal.h"
#include "EEndCharacterAttachEffectResourceCategoryType.generated.h"

UENUM(BlueprintType)
enum class EEndCharacterAttachEffectResourceCategoryType : uint8 {
    Resident,
    Character,
    ResourceCharacter,
    ResourceLevel,
};

