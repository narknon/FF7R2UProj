#pragma once
#include "CoreMinimal.h"
#include "EndAnimationSettingsContact.generated.h"

USTRUCT(BlueprintType)
struct FEndAnimationSettingsContact {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float NoInputCancelTimeInWalk;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float NoInputCancelTimeInRun;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 NoInputRetryCountMax;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SameCharacterRetryInterval;
    
    ENDGAME_API FEndAnimationSettingsContact();
};

