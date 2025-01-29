#pragma once
#include "CoreMinimal.h"
#include "EndBoneBlendRate.h"
#include "EndBoneBlendRateGroup.generated.h"

USTRUCT(BlueprintType)
struct FEndBoneBlendRateGroup {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndBoneBlendRate> BoneBlendRates;
    
    ENDGAME_API FEndBoneBlendRateGroup();
};

