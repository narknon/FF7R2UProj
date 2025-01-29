#pragma once
#include "CoreMinimal.h"
#include "EEndBattleAbilityCommandType.h"
#include "EEndAIReactionPlayerType.h"
#include "EndAIReactionInfoCommand.generated.h"

USTRUCT(BlueprintType)
struct FEndAIReactionInfoCommand {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndBattleAbilityCommandType CommandType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIReactionPlayerType PlayerType;
    
    ENDGAME_API FEndAIReactionInfoCommand();
};

