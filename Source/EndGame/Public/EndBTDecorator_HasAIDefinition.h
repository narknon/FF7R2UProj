#pragma once
#include "CoreMinimal.h"
#include "EEndAIActionDefinition.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_HasAIDefinition.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_HasAIDefinition : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndAIActionDefinition> AIDefinitionTypes;
    
    UEndBTDecorator_HasAIDefinition();

};

