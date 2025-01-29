#pragma once
#include "CoreMinimal.h"
#include "EndAIInterestAction.h"
#include "EndAIInterestActionPlayBeginLoopAnimation.generated.h"

class UAnimSequenceBase;

USTRUCT(BlueprintType)
struct ENDGAME_API FEndAIInterestActionPlayBeginLoopAnimation : public FEndAIInterestAction {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    FName BeginAnimationName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    UAnimSequenceBase* BeginAnimation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    FName LoopAnimationName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    UAnimSequenceBase* LoopAnimation;
    
    FEndAIInterestActionPlayBeginLoopAnimation();
};

