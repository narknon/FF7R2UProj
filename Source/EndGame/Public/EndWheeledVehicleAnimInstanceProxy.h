#pragma once
#include "CoreMinimal.h"
#include "EndSkeletalMeshActorAnimInstanceProxy.h"
#include "EndWheeledVehicleAnimInstanceProxy.generated.h"

USTRUCT(BlueprintType)
struct FEndWheeledVehicleAnimInstanceProxy : public FEndSkeletalMeshActorAnimInstanceProxy {
    GENERATED_BODY()
public:
    ENDGAME_API FEndWheeledVehicleAnimInstanceProxy();
};

