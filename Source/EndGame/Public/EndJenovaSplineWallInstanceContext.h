#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndJenovaSplineWallInstanceContext.generated.h"

USTRUCT(BlueprintType)
struct FEndJenovaSplineWallInstanceContext {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 InstanceIndex;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float HorizontalRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BaseScale;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTransform CurrentTransform;
    
    ENDGAME_API FEndJenovaSplineWallInstanceContext();
};

