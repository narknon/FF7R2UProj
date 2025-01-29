#pragma once
#include "CoreMinimal.h"
#include "EndAIEnemyRightToAttackInfo.generated.h"

USTRUCT(BlueprintType)
struct FEndAIEnemyRightToAttackInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 CountMax;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float IntervalMax;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 ApplyMembrsNumLine;
    
    ENDGAME_API FEndAIEnemyRightToAttackInfo();
};

