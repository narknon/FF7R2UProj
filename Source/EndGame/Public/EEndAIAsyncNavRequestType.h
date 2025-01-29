#pragma once
#include "CoreMinimal.h"
#include "EEndAIAsyncNavRequestType.generated.h"

UENUM(BlueprintType)
enum class EEndAIAsyncNavRequestType : uint8 {
    FindPath,
    FindPathFilter,
    NavMeshPathDistance,
    NavMeshPathDistanceFilter,
    IsConnectedNavMeshPathFilter,
};

