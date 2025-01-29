#pragma once
#include "CoreMinimal.h"
#include "EndCutSummonerJumpItem.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndCutSummonerJumpItem {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ActorName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Destination;
    
    FEndCutSummonerJumpItem();
};

