#pragma once
#include "CoreMinimal.h"
#include "EndFieldOneShotAccessAnimUnit.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldOneShotAccessAnimUnit {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName PlayAnimationName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BlendInTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BlendOutTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float StartSequenceRate;
    
    ENDGAME_API FEndFieldOneShotAccessAnimUnit();
};

