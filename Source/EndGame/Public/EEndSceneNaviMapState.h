#pragma once
#include "CoreMinimal.h"
#include "EEndSceneNaviMapState.generated.h"

UENUM()
enum class EEndSceneNaviMapState : int32 {
    Unopened,
    Opened,
    Visited,
};

