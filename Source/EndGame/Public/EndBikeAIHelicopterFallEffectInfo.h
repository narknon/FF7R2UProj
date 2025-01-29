#pragma once
#include "CoreMinimal.h"
#include "EndBikeAIHelicopterFallEffectInfo.generated.h"

USTRUCT(BlueprintType)
struct FEndBikeAIHelicopterFallEffectInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName EffectName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float HorizontalOffset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float VerticalOffset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Rotation;
    
    ENDGAME_API FEndBikeAIHelicopterFallEffectInfo();
};

