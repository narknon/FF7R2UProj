#pragma once
#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "EndAIMoveDefinitionSequenceInfo.generated.h"

class UEndAIMoveDefinition;

USTRUCT(BlueprintType)
struct FEndAIMoveDefinitionSequenceInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndAIMoveDefinition> MoveDefinitionClass;
    
    ENDGAME_API FEndAIMoveDefinitionSequenceInfo();
};

