#pragma once
#include "CoreMinimal.h"
#include "EEndBikeDamageSourcePositionBaseType.generated.h"

UENUM(BlueprintType)
enum class EEndBikeDamageSourcePositionBaseType : uint8 {
    Owner,
    OwnerWeapon1,
    OwnerWeapon2,
    OwnerWeapon3,
    OwnerWeapon4,
    Target = 10,
    TargetWeapon1,
    TargetWeapon2,
    TargetWeapon3,
    TargetWeapon4,
    ParentDamageSource = 20,
    HitPosition,
    TargetLocation,
    FieldLocation,
    FieldLaunchLocation,
    EnvironmentActor,
};

