#pragma once
#include "CoreMinimal.h"
#include "EndDolphinJumpSplinePhaseData.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndDolphinJumpSplinePhaseData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float StartDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SwimmingDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool DisableUserControll;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool MoveToCenterLine;
    
    FEndDolphinJumpSplinePhaseData();
};

