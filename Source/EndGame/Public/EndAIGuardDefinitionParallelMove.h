#pragma once
#include "CoreMinimal.h"
#include "EndAIGuardDefinition.h"
#include "Templates/SubclassOf.h"
#include "EndAIGuardDefinitionParallelMove.generated.h"

class UEndAIMoveDefinition;

UCLASS(Blueprintable)
class UEndAIGuardDefinitionParallelMove : public UEndAIGuardDefinition {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndAIMoveDefinition> MoveDefinitionClass;
    
    UEndAIGuardDefinitionParallelMove();

};

