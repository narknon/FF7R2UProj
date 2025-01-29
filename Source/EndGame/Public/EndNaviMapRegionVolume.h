#pragma once
#include "CoreMinimal.h"
#include "EndSplineBrushVolume.h"
#include "EndNaviMapRegionVolume.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class AEndNaviMapRegionVolume : public AEndSplineBrushVolume {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName LocationId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName NaviMapId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName RegionName;
    
    AEndNaviMapRegionVolume(const FObjectInitializer& ObjectInitializer);

};

