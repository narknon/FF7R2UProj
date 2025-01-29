#pragma once
#include "CoreMinimal.h"
#include "ChocoboRaceGimmickSplineWaitPoint.generated.h"

USTRUCT(BlueprintType)
struct FChocoboRaceGimmickSplineWaitPoint {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float InputKey;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float WaitTime;
    
    ENDGAME_API FChocoboRaceGimmickSplineWaitPoint();
};

