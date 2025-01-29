#pragma once
#include "CoreMinimal.h"
#include "EndAIInterestAction.h"
#include "EndAIInterestActionEmotion.generated.h"

class AActor;

USTRUCT(BlueprintType)
struct ENDGAME_API FEndAIInterestActionEmotion : public FEndAIInterestAction {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    FName EmotionID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    float LoopTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    bool InterestDirection;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TWeakObjectPtr<AActor> TargetActor;
    
    FEndAIInterestActionEmotion();
};

