#pragma once
#include "CoreMinimal.h"
#include "EndAIAbilityDefinition.h"
#include "EndAIAbilityDefinitionEB2090.generated.h"

UCLASS(Blueprintable)
class UEndAIAbilityDefinitionEB2090 : public UEndAIAbilityDefinition {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ActiveDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MoveExtraTime;
    
    UEndAIAbilityDefinitionEB2090();

};

