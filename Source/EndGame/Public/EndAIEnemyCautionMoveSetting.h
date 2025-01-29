#pragma once
#include "CoreMinimal.h"
#include "EndAIMoveDefinitionMoveApproach.h"
#include "EndAIEnemyCautionMoveSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndAIEnemyCautionMoveSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAIMoveDefinitionMoveApproach MoveApproachLeave;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Distance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAIMoveDefinitionMoveApproach MoveKeep;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DistanceKeepMin;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DistanceKeepMax;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MoveWaitMin;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MoveWaitMax;
    
    ENDGAME_API FEndAIEnemyCautionMoveSetting();
};

