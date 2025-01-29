#pragma once
#include "CoreMinimal.h"
#include "EndAIMoveDefinitionConfrontBase.h"
#include "EndAIMoveDefinitionConfrontToAction.generated.h"

UCLASS(Blueprintable)
class UEndAIMoveDefinitionConfrontToAction : public UEndAIMoveDefinitionConfrontBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bStepAfterPlayAction;
    
    UEndAIMoveDefinitionConfrontToAction();

};

