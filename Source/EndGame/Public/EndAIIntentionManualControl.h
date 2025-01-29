#pragma once
#include "CoreMinimal.h"
#include "EndAIIntention.h"
#include "EndAIIntentionManualControl.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndAIIntentionManualControl : public FEndAIIntention {
    GENERATED_BODY()
public:
    FEndAIIntentionManualControl();
};

