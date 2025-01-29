#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndObjectNodeInfo.generated.h"

USTRUCT(BlueprintType)
struct FEndObjectNodeInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector2D pos;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Comment;
    
    ENDGAME_API FEndObjectNodeInfo();
};

