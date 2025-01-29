#pragma once
#include "CoreMinimal.h"
#include "EndAIActionPackReturnInfo.generated.h"

USTRUCT(BlueprintType)
struct FEndAIActionPackReturnInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bSuccess;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SelectedTag;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ActionPackTag;
    
    ENDGAME_API FEndAIActionPackReturnInfo();
};

