#pragma once
#include "CoreMinimal.h"
#include "EEndAiMoveType.h"
#include "EndAIMoveDefinitionMoveApproach.generated.h"

USTRUCT(BlueprintType)
struct FEndAIMoveDefinitionMoveApproach {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAiMoveType MoveType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bStrafe;
    
    ENDGAME_API FEndAIMoveDefinitionMoveApproach();
};

