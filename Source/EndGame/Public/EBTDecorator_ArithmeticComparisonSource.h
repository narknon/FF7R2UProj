#pragma once
#include "CoreMinimal.h"
#include "EBTDecorator_ArithmeticComparisonSource.generated.h"

UENUM(BlueprintType)
enum class EBTDecorator_ArithmeticComparisonSource : uint8 {
    Blackboard,
    ActorProperty,
    ActorFunction,
    LiteralValue,
};

