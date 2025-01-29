#pragma once
#include "CoreMinimal.h"
#include "EEndPhysicsStaticMeshCollisionPresetType.generated.h"

UENUM(BlueprintType)
enum class EEndPhysicsStaticMeshCollisionPresetType : uint8 {
    AffectCharacterMove,
    NotAffectCharacterMove,
};

