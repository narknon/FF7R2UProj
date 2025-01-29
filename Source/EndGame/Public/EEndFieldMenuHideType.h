#pragma once
#include "CoreMinimal.h"
#include "EEndFieldMenuHideType.generated.h"

UENUM()
enum class EEndFieldMenuHideType : uint8 {
    EEndFieldMenuHideType_FieldMenu = 1,
    EEndFieldMenuHideType_Pane,
    EEndFieldMenuHideType_HideFieldCommandMenu = 4,
    EndBattleMode_Max UMETA(Hidden),
};

