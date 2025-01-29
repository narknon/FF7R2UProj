#pragma once
#include "CoreMinimal.h"
#include "EEndMovieClipMode.generated.h"

UENUM()
enum class EEndMovieClipMode : uint8 {
    Load = 1,
    Play,
    Draw,
};

