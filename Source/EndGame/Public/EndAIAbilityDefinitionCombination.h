#pragma once
#include "CoreMinimal.h"
#include "EndAIAbilityDefinition.h"
#include "EndAIAbilityDefinitionCombination.generated.h"

UCLASS(Blueprintable)
class UEndAIAbilityDefinitionCombination : public UEndAIAbilityDefinition {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName CombinationId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName GroupIndividualTag;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bLastCombination;
    
    UEndAIAbilityDefinitionCombination();

};

