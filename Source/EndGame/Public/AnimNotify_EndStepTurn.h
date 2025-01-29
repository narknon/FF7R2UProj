#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EEndStepTurnTiming.h"
#include "AnimNotify_EndStepTurn.generated.h"

UCLASS(Blueprintable, CollapseCategories)
class UAnimNotify_EndStepTurn : public UAnimNotify {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndStepTurnTiming Timing;
    
    UAnimNotify_EndStepTurn();

};

