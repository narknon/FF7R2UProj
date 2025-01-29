#pragma once
#include "CoreMinimal.h"
#include "EndBoneBlendRate.generated.h"

USTRUCT(BlueprintType)
struct FEndBoneBlendRate {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName BoneName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BlendRate;
    
    ENDGAME_API FEndBoneBlendRate();
};

