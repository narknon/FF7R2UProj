#pragma once
#include "CoreMinimal.h"
#include "GrassGridOctTreeNode.generated.h"

USTRUCT(BlueprintType)
struct FGrassGridOctTreeNode {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 Value_;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<uint32> ChildIndicies_;
    
    ENDGAME_API FGrassGridOctTreeNode();
};

