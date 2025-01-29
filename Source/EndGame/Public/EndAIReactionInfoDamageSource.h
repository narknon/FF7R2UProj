#pragma once
#include "CoreMinimal.h"
#include "EEndAIReactionPlayerType.h"
#include "EndAIReactionInfoDamageSource.generated.h"

USTRUCT(BlueprintType)
struct FEndAIReactionInfoDamageSource {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName DamageSourceID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIReactionPlayerType PlayerType;
    
    ENDGAME_API FEndAIReactionInfoDamageSource();
};

