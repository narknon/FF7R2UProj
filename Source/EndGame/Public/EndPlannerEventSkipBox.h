#pragma once
#include "CoreMinimal.h"
#include "EndTriggerBox.h"
#include "EndPlannerEventSkipBox.generated.h"

UCLASS(Blueprintable)
class AEndPlannerEventSkipBox : public AEndTriggerBox {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> TargetTalkIDs;
    
    AEndPlannerEventSkipBox(const FObjectInitializer& ObjectInitializer);

};

