#pragma once
#include "CoreMinimal.h"
#include "EndCutStoryFlagConditionItem.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndCutStoryFlagConditionItem {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool Condition;
    
    FEndCutStoryFlagConditionItem();
};

