#pragma once
#include "CoreMinimal.h"
#include "EndBikeAIHelicopterLockOnInfo.generated.h"

USTRUCT(BlueprintType)
struct FEndBikeAIHelicopterLockOnInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName DamageSourceID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DelayTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool Tracking;
    
    ENDGAME_API FEndBikeAIHelicopterLockOnInfo();
};

