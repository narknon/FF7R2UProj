#pragma once
#include "CoreMinimal.h"
#include "EndSwitchingAnimStatus.generated.h"

UENUM(BlueprintType)
enum class EndSwitchingAnimStatus : uint8 {
    EndSwitchingAnimStatus_Outer,
    EndSwitchingAnimStatus_Inner,
    EndSwitchingAnimStatus_OuterInner,
    EndSwitchingAnimStatus_InnerOuter,
};

