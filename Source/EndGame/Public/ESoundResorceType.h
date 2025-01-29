#pragma once
#include "CoreMinimal.h"
#include "ESoundResorceType.generated.h"

UENUM(BlueprintType)
enum class ESoundResorceType : uint8 {
    ESoundResorceType_SE,
    ESoundResorceType_Voice,
    ESoundResorceType_AutoSE,
    ESoundResorceType_FootAttributeSE,
};

