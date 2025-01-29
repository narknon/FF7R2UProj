#pragma once
#include "CoreMinimal.h"
#include "EActorAiMode.generated.h"

UENUM(BlueprintType)
enum class EActorAiMode : uint8 {
    EActorAiMode_CINEMA,
    EActorAiMode_PLAYER,
    EActorAiMode_FIELD,
    EActorAiMode_BATTLE,
    EActorAiMode_AI,
};

