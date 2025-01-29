#pragma once
#include "CoreMinimal.h"
#include "EndBikeAIEffectInfo.generated.h"

USTRUCT(BlueprintType)
struct FEndBikeAIEffectInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName EffectName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SocketName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float HpAmount;
    
    ENDGAME_API FEndBikeAIEffectInfo();
};

