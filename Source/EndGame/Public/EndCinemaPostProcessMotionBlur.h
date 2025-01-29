#pragma once
#include "CoreMinimal.h"
#include "EndCinemaPostProcessActor.h"
#include "EndCinemaPostProcessMotionBlur.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndCinemaPostProcessMotionBlur : public AEndCinemaPostProcessActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool EnabledShutter;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Shutter;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool EnabledLimitation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Limitation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool EnabledWeight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Weight;
    
    AEndCinemaPostProcessMotionBlur(const FObjectInitializer& ObjectInitializer);

};

