#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndSBScooterExpressionParameter.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndSBScooterExpressionParameter {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FFloatInterval SuspensionRange;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FFloatInterval SlopeAngleRange;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MinSlopeAngleRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FloorNormalInterpSpeedOnRiding;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FloorNormalInterpSpeed;
    
    FEndSBScooterExpressionParameter();
};

