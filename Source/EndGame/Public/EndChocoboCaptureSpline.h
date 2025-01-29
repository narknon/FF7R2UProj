#pragma once
#include "CoreMinimal.h"
#include "ChocoboCaptureStopPoint.h"
#include "EndSplineActorBase.h"
#include "EndChocoboCaptureSpline.generated.h"

UCLASS(Blueprintable)
class AEndChocoboCaptureSpline : public AEndSplineActorBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FChocoboCaptureStopPoint> _StopPoint;
    
    AEndChocoboCaptureSpline(const FObjectInitializer& ObjectInitializer);

};

