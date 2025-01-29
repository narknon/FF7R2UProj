#pragma once
#include "CoreMinimal.h"
#include "EShortCutCommandType.generated.h"

UENUM(BlueprintType)
enum class EShortCutCommandType : uint8 {
    EShortCutCommandType_FACEBUTTON_LEFT,
    EShortCutCommandType_L1_FACEBUTTON_TOP,
    EShortCutCommandType_L1_FACEBUTTON_BOTTOM,
    EShortCutCommandType_FACEBUTTON_TOP,
    EShortCutCommandType_L1_FACEBUTTON_LEFT,
    EShortCutCommandType_L1_FACEBUTTON_RIGHT,
};

