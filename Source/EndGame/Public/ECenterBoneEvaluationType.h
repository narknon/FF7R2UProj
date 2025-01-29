#pragma once
#include "CoreMinimal.h"
#include "ECenterBoneEvaluationType.generated.h"

UENUM(BlueprintType)
enum class ECenterBoneEvaluationType : uint8 {
    TranslationAndRotation,
    Translation,
    Rotation,
    Ignore,
};

