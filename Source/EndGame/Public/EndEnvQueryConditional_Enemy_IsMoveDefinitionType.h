#pragma once
#include "CoreMinimal.h"
#include "EnvQueryConditional.h"
#include "EEndAIMoveDefinition.h"
#include "EndEnvQueryConditional_Enemy_IsMoveDefinitionType.generated.h"

UCLASS(Blueprintable)
class UEndEnvQueryConditional_Enemy_IsMoveDefinitionType : public UEnvQueryConditional {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndAIMoveDefinition> MoveDefinitionTypes;
    
    UEndEnvQueryConditional_Enemy_IsMoveDefinitionType();

};

