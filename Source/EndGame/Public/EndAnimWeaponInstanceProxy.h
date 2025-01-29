#pragma once
#include "CoreMinimal.h"
#include "EndSkeletalMeshActorAnimInstanceProxy.h"
#include "EndAnimWeaponInstanceProxy.generated.h"

USTRUCT(BlueprintType)
struct FEndAnimWeaponInstanceProxy : public FEndSkeletalMeshActorAnimInstanceProxy {
    GENERATED_BODY()
public:
    ENDGAME_API FEndAnimWeaponInstanceProxy();
};

