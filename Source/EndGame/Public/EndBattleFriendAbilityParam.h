#pragma once
#include "CoreMinimal.h"
#include "EndBattleFriendAbilityParam.generated.h"

USTRUCT(BlueprintType)
struct FEndBattleFriendAbilityParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AbilityId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Probability;
    
    ENDGAME_API FEndBattleFriendAbilityParam();
};

