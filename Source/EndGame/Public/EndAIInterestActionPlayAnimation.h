#pragma once
#include "CoreMinimal.h"
#include "EndAIInterestAction.h"
#include "EndAIInterestActionPlayAnimation.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndAIInterestActionPlayAnimation : public FEndAIInterestAction {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    FName LevelName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    FName AnimationName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    bool IsLoop;
    
    FEndAIInterestActionPlayAnimation();
};

