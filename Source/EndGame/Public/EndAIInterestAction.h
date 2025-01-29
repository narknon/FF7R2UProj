#pragma once
#include "CoreMinimal.h"
#include "EEndAIIntentionPriority.h"
#include "EEndAIInterestActionState.h"
#include "EEndAIInterestActionTag.h"
#include "EndAIInterestAction.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndAIInterestAction {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUpdatableWhenAIStop;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    FName Name;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TArray<EEndAIInterestActionTag> Tags;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    EEndAIIntentionPriority Priority;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    EEndAIInterestActionState CurrentState;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 Index;
    
    FEndAIInterestAction();
};

