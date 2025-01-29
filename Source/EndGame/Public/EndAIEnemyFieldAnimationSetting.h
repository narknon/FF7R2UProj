#pragma once
#include "CoreMinimal.h"
#include "EndAIEnemyFieldAnimationSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndAIEnemyFieldAnimationSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AnimName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bCanSuspend;
    
    ENDGAME_API FEndAIEnemyFieldAnimationSetting();
};

