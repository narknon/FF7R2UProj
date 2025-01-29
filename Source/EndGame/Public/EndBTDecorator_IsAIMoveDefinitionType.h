#pragma once
#include "CoreMinimal.h"
#include "EEndAIMoveDefinition.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_IsAIMoveDefinitionType.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_IsAIMoveDefinitionType : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndAIMoveDefinition> Types;
    
    UEndBTDecorator_IsAIMoveDefinitionType();

};

