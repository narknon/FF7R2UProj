#pragma once
#include "CoreMinimal.h"
#include "EEndAIReactionPlayerType.h"
#include "EndAIReactionInfoAbility.generated.h"

USTRUCT(BlueprintType)
struct FEndAIReactionInfoAbility {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AbilityId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIReactionPlayerType PlayerType;
    
    ENDGAME_API FEndAIReactionInfoAbility();
};

