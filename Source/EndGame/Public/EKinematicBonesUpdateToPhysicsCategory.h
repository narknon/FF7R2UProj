#pragma once
#include "CoreMinimal.h"
#include "EKinematicBonesUpdateToPhysicsCategory.generated.h"

UENUM(BlueprintType)
enum class EKinematicBonesUpdateToPhysicsCategory : uint8 {
    BehaviorMode,
    ActorType,
    Ragdoll,
    MiniGame,
    Vehicle,
};

