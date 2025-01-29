#pragma once
#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "EndAIActionPackInfo.generated.h"

class UEndAIActionDefinitionBase;
class UEndAIMoveDefinition;

USTRUCT(BlueprintType)
struct FEndAIActionPackInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndAIMoveDefinition> MoveDefinitionClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndAIActionDefinitionBase> ActionDefinitionClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float LotProbability;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bFastSelect;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Tag;
    
    ENDGAME_API FEndAIActionPackInfo();
};

