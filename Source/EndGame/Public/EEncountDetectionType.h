#pragma once
#include "CoreMinimal.h"
#include "EEncountDetectionType.generated.h"

UENUM(BlueprintType)
enum class EEncountDetectionType : uint8 {
    None,
    ViewDetection,
    ListenDetection,
};

