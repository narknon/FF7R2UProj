#pragma once
#include "CoreMinimal.h"
#include "EFA0222ExtraAction_PoseReference.generated.h"

UENUM(BlueprintType)
enum class EFA0222ExtraAction_PoseReference : uint8 {
    CenterHandle,
    UpHandle,
    DownHandle,
    LeftHandle,
    RightHandle,
};

