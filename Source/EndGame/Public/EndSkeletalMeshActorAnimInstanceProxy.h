#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimSingleNodeInstanceProxy.h"
#include "EndSkeletalMeshActorAnimInstanceProxy.generated.h"

USTRUCT(BlueprintType)
struct FEndSkeletalMeshActorAnimInstanceProxy : public FAnimSingleNodeInstanceProxy {
    GENERATED_BODY()
public:
    ENDGAME_API FEndSkeletalMeshActorAnimInstanceProxy();
};

