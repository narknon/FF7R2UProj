#pragma once
#include "CoreMinimal.h"
#include "EActorMode.generated.h"

UENUM(BlueprintType)
enum class EActorMode : uint8 {
    EActorMode_NONE,
    EActorMode_FIELD,
    EActorMode_FIELD_CINEMA,
    EActorMode_CAUTION,
    EActorMode_BATTLE,
    EActorMode_CINEMA,
};

