#pragma once
#include "CoreMinimal.h"
#include "EEndLayer.generated.h"

UENUM(BlueprintType)
enum class EEndLayer : uint8 {
    EEndLayer_Normal,
    EEndLayer_MiniGame,
    EEndLayer_AIMove,
    EEndLayer_AI,
    EEndLayer_Field,
    EEndLayer_Animation,
    EEndLayer_Notify,
    EEndLayer_Battle,
    EEndLayer_BattleBurst,
    EEndLayer_BattleSyncAction,
    EEndLayer_Cinema,
    EEndLayer_Attach,
    EEndLayer_Debug,
};

