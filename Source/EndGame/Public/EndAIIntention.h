#pragma once
#include "CoreMinimal.h"
#include "EEndAIIntentionPriority.h"
#include "EndAIIntention.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndAIIntention {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUpdatableWhenAIStop;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIIntentionPriority Priority;
    
    FEndAIIntention();
};

