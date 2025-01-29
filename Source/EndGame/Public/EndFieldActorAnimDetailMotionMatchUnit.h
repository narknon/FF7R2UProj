#pragma once
#include "CoreMinimal.h"
#include "EndFieldActorAnimDetailMotionMatchUnit.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldActorAnimDetailMotionMatchUnit {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MotionName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float StartFrameRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float StartFrameSec;
    
    ENDGAME_API FEndFieldActorAnimDetailMotionMatchUnit();
};

