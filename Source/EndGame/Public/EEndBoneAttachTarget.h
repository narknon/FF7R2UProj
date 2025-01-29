#pragma once
#include "CoreMinimal.h"
#include "EEndBoneAttachTarget.generated.h"

UENUM(BlueprintType)
enum class EEndBoneAttachTarget : uint8 {
    None,
    OwnerCharacter,
    OwnerParentCharacter,
    ManualCharacter,
    ManualTransform,
    ManualTranslation,
};

