#pragma once
#include "CoreMinimal.h"
#include "EDisableSimulatePhysicsMask.generated.h"

UENUM(BlueprintType)
enum class EDisableSimulatePhysicsMask : uint8 {
    SP_Init,
    SP_System,
    SP_Manager,
    SP_Battle,
    SP_Field,
    SP_MiniGame,
    SP_Self,
    SP_Streaming,
    SP_Attach,
    SP_Invalid,
    SP_Debug,
    SP_Max,
};

