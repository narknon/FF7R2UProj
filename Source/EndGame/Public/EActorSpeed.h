#pragma once
#include "CoreMinimal.h"
#include "EActorSpeed.generated.h"

UENUM(BlueprintType)
enum class EActorSpeed : uint8 {
    EActorSpeed_BATTLE_CAMERA,
    EActorSpeed_BATTLE_HIT,
    EActorSpeed_CUT,
    EActorSpeed_DEBUG,
};

