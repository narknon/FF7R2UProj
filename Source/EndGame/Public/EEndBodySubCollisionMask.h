#pragma once
#include "CoreMinimal.h"
#include "EEndBodySubCollisionMask.generated.h"

UENUM(BlueprintType)
enum class EEndBodySubCollisionMask : uint8 {
    Field,
    Battle,
    AI,
    FieldAction,
    ChangeAppearance,
    ComponentField,
    TurnBack,
    MiniGame,
    Max,
};

