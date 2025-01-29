#pragma once
#include "CoreMinimal.h"
#include "ChocoboCraftQuestPoint.h"
#include "ChocoboCraftQuestWave.h"
#include "EndSplineActorBase.h"
#include "EndChocoboCraftQuestSpline.generated.h"

UCLASS(Blueprintable)
class AEndChocoboCraftQuestSpline : public AEndSplineActorBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SmellTargetPoint;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FChocoboCraftQuestPoint> QuestInfo;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DistanceBetweenFirstPoints;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float HeightRequiredOnAdjustedPoint;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUpdateEndAndStartPoints;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bSimulateWave;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FChocoboCraftQuestWave> WaveInfo;
    
    AEndChocoboCraftQuestSpline(const FObjectInitializer& ObjectInitializer);

};

