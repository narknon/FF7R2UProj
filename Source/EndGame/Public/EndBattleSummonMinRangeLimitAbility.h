#pragma once
#include "CoreMinimal.h"
#include "EndBattleSummonMinRangeLimitAbility.generated.h"

USTRUCT(BlueprintType)
struct FEndBattleSummonMinRangeLimitAbility {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AbilityId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MinRange;
    
    ENDGAME_API FEndBattleSummonMinRangeLimitAbility();
};

