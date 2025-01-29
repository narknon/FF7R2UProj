#pragma once
#include "CoreMinimal.h"
#include "BoneContainer.h"
#include "EndReinsChainBone.generated.h"

USTRUCT(BlueprintType)
struct FEndReinsChainBone {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FBoneReference BeginChainBone;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FBoneReference EndChainBone;
    
    ENDGAME_API FEndReinsChainBone();
};

