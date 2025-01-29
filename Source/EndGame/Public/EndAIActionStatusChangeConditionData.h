#pragma once
#include "CoreMinimal.h"
#include "EEndAILogicalOperator.h"
#include "EndAIActionStatusChangeConditionData.generated.h"

USTRUCT(BlueprintType)
struct FEndAIActionStatusChangeConditionData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAILogicalOperator LogicalOperator;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bNot;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> StatusChangeIds;
    
    ENDGAME_API FEndAIActionStatusChangeConditionData();
};

