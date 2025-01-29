#pragma once
#include "CoreMinimal.h"
#include "EBallSpawnCondition.h"
#include "BallSpawnConditionData.generated.h"

USTRUCT(BlueprintType)
struct FBallSpawnConditionData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EBallSpawnCondition SpawnCondition;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 BallConditionVariable;
    
    ENDGAME_API FBallSpawnConditionData();
};

