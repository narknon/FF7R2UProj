#pragma once
#include "CoreMinimal.h"
#include "EndAIActionDefinition.h"
#include "EndAICombinationAbilityDefinition.generated.h"

UCLASS(Blueprintable)
class UEndAICombinationAbilityDefinition : public UEndAIActionDefinition {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName CombinationAbilityId;
    
    UEndAICombinationAbilityDefinition();

};

