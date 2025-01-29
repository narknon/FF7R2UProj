#pragma once
#include "CoreMinimal.h"
#include "EEndMenuTalkViewType.generated.h"

UENUM(BlueprintType)
enum class EEndMenuTalkViewType : uint8 {
    Both,
    OnlyText,
    Hidden,
};

