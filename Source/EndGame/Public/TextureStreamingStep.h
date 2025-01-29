#pragma once
#include "CoreMinimal.h"
#include "TextureStreamingStep.generated.h"

UENUM(BlueprintType)
enum class TextureStreamingStep : uint8 {
    None,
    WaitMassive,
    Wait,
    Finish,
};

