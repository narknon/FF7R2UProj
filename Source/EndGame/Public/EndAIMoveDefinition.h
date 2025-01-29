#pragma once
#include "CoreMinimal.h"
#include "EndAIActionDefinitionBase.h"
#include "EndAIMoveDefinition.generated.h"

UCLASS(Blueprintable)
class UEndAIMoveDefinition : public UEndAIActionDefinitionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bNotActionInterrupt;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bNotReactionAction;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MoveDefTag;
    
    UEndAIMoveDefinition();

};

