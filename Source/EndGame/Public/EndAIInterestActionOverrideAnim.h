#pragma once
#include "CoreMinimal.h"
#include "EndAIInterestAction.h"
#include "EndAIInterestActionOverrideAnim.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndAIInterestActionOverrideAnim : public FEndAIInterestAction {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    FName OverrideBehaviorMode;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    int32 OverrideAnimSetID;
    
    FEndAIInterestActionOverrideAnim();
};

