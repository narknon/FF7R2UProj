#pragma once
#include "CoreMinimal.h"
#include "EEndEffectStaticMeshSelectKind.generated.h"

UENUM()
enum class EEndEffectStaticMeshSelectKind : int8 {
    Random,
    Order,
    UserSet,
    RandomUserSet,
    Surface_Random,
    Surface_Order,
};

