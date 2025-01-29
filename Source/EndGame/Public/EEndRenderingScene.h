#pragma once
#include "CoreMinimal.h"
#include "EEndRenderingScene.generated.h"

UENUM(BlueprintType)
enum class EEndRenderingScene : uint8 {
    Default,
    MainMenu,
    MiniGame,
    Max,
};

