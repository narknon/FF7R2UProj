#pragma once
#include "CoreMinimal.h"
#include "EEndUpperBodyActionLayer.generated.h"

UENUM(BlueprintType)
enum class EEndUpperBodyActionLayer : uint8 {
    BarretSunglass,
    CallChocobo,
    CallBuggy,
    SearchCactusRock,
    WorldReport,
    Memo,
    FaceGuard,
    Unknown,
    Max,
};

