#pragma once
#include "CoreMinimal.h"
#include "EndFieldOneShotMoveAnimUnit.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldOneShotMoveAnimUnit {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName PlayAnimationName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> MotionMatchAnimationNames;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BlendInTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BlendOutTime;
    
    ENDGAME_API FEndFieldOneShotMoveAnimUnit();
};

