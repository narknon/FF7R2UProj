#pragma once
#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EEndAIMoveDefinition.h"
#include "EndEnvQueryTest_Enemy_IsMoveDefinitionType.generated.h"

UCLASS(Blueprintable)
class UEndEnvQueryTest_Enemy_IsMoveDefinitionType : public UEnvQueryTest {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndAIMoveDefinition> MoveDefinitionTypes;
    
    UEndEnvQueryTest_Enemy_IsMoveDefinitionType();

};

