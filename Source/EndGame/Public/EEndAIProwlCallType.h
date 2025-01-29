#pragma once
#include "CoreMinimal.h"
#include "EEndAIProwlCallType.generated.h"

UENUM(BlueprintType)
enum class EEndAIProwlCallType : uint8 {
    Normal,
    Cancel,
    ChangeCharaState,
    Max,
    None,
};

