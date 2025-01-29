#pragma once
#include "CoreMinimal.h"
#include "AssignmentParam.generated.h"

USTRUCT(BlueprintType)
struct FAssignmentParam {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName objectID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName attributeID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName stateChangeID;
    
    ENDGAME_API FAssignmentParam();
};

