#pragma once
#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "EndAIActionDefinitionSet.generated.h"

class UEndAIActionDefinitionBase;
class UEndAIMoveDefinition;

USTRUCT(BlueprintType)
struct FEndAIActionDefinitionSet {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndAIMoveDefinition> MoveDefinitionClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndAIActionDefinitionBase> ActionDefinitionClass;
    
    ENDGAME_API FEndAIActionDefinitionSet();
};

