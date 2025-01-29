#pragma once
#include "CoreMinimal.h"
#include "EndFieldActionTinyBroncoSplineMoveInputScaleData.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldActionTinyBroncoSplineMoveInputScaleData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float InputKey;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float InputScale;
    
    ENDGAME_API FEndFieldActionTinyBroncoSplineMoveInputScaleData();
};

