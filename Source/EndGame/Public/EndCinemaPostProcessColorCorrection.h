#pragma once
#include "CoreMinimal.h"
#include "EndCinemaPostProcessActor.h"
#include "EndCinemaPostProcessColorCorrection.generated.h"

class UVolumeTexture;

UCLASS(Blueprintable)
class ENDGAME_API AEndCinemaPostProcessColorCorrection : public AEndCinemaPostProcessActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Interp, meta=(AllowPrivateAccess=true))
    bool EnabledColorCorrection;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UVolumeTexture* VolumeTexture;
    
    AEndCinemaPostProcessColorCorrection(const FObjectInitializer& ObjectInitializer);

};

