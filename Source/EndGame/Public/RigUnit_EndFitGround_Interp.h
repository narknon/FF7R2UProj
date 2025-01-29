#pragma once
#include "CoreMinimal.h"
#include "RigUnit_EndFitGround_Interp.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndFitGround_Interp {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float GroundHeightInterpSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float GroundNormalFitAngleInterpSpeed;
    
    ENDGAME_API FRigUnit_EndFitGround_Interp();
};

