#pragma once
#include "CoreMinimal.h"
#include "EEndAIReactionInfoOtherType.h"
#include "EEndAIReactionPlayerType.h"
#include "EndAIReactionInfoOther.generated.h"

USTRUCT(BlueprintType)
struct FEndAIReactionInfoOther {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIReactionInfoOtherType OtherType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIReactionPlayerType PlayerType;
    
    ENDGAME_API FEndAIReactionInfoOther();
};

