#pragma once
#include "CoreMinimal.h"
#include "EndTargetPointParameters.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndTargetPointParameters {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bWarpPoint;
    
    FEndTargetPointParameters();
};

