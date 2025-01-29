#pragma once
#include "CoreMinimal.h"
#include "EndAIActionDefinition.h"
#include "EndAIAnimDefinition.generated.h"

UCLASS(Blueprintable)
class UEndAIAnimDefinition : public UEndAIActionDefinition {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AnimName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bApplyTimeCoefficient;
    
    UEndAIAnimDefinition();

};

