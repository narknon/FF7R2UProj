#pragma once
#include "CoreMinimal.h"
#include "EndAIAbilityDefinition.h"
#include "Templates/SubclassOf.h"
#include "EndAIAbilityDefinitionParallelMove.generated.h"

class UEndAIMoveDefinition;

UCLASS(Blueprintable)
class UEndAIAbilityDefinitionParallelMove : public UEndAIAbilityDefinition {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndAIMoveDefinition> MoveDefinitionClass;
    
    UEndAIAbilityDefinitionParallelMove();

};

