#pragma once
#include "CoreMinimal.h"
#include "EEndLookAtForceDeactiveType.h"
#include "EndAIInterestAction.h"
#include "EndAIInterestActionLookAtForceDeactive.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndAIInterestActionLookAtForceDeactive : public FEndAIInterestAction {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    EEndLookAtForceDeactiveType Type;
    
    FEndAIInterestActionLookAtForceDeactive();
};

