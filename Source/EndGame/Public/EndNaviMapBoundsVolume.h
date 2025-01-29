#pragma once
#include "CoreMinimal.h"
#include "EndSplineBrushVolume.h"
#include "EndNaviMapBoundsVolume.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class AEndNaviMapBoundsVolume : public AEndSplineBrushVolume {
    GENERATED_BODY()
public:
    AEndNaviMapBoundsVolume(const FObjectInitializer& ObjectInitializer);

};

