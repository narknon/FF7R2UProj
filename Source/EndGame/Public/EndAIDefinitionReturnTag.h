#pragma once
#include "CoreMinimal.h"
#include "EndAIDefinitionReturnTag.generated.h"

USTRUCT(BlueprintType)
struct FEndAIDefinitionReturnTag {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MoveDefinitionTag;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ActionDefinitionTag;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ComboDefinitionTag;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ComboConnectDefinitionTag;
    
    ENDGAME_API FEndAIDefinitionReturnTag();
};

