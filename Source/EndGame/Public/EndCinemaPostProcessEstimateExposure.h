#pragma once
#include "CoreMinimal.h"
#include "EndCinemaPostProcessActor.h"
#include "EndCinemaPostProcessEstimateExposure.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndCinemaPostProcessEstimateExposure : public AEndCinemaPostProcessActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool EnabledActivated;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool Activated;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool EnabledVariance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Variance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool EnabledWeight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Weight;
    
    AEndCinemaPostProcessEstimateExposure(const FObjectInitializer& ObjectInitializer);

};

