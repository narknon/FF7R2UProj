#pragma once
#include "CoreMinimal.h"
#include "EndCutChangePartsItem.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndCutChangePartsItem {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MeshName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MeshLabel;
    
    FEndCutChangePartsItem();
};

