#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndFieldStartPointBase.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldStartPointBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTransform TargetTransform;
    
    ENDGAME_API FEndFieldStartPointBase();
};

