#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndBikeEnemyWithdrawalParam.generated.h"

USTRUCT(BlueprintType)
struct FEndBikeEnemyWithdrawalParam {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FFloatInterval AliveTimeRange;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FFloatInterval AliveForwardDistanceRange;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AliveRightDirDistance;
    
    ENDGAME_API FEndBikeEnemyWithdrawalParam();
};

