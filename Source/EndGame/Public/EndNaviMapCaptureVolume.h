#pragma once
#include "CoreMinimal.h"
#include "EndSplineBrushVolume.h"
#include "EndNaviMapCaptureVolume.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class AEndNaviMapCaptureVolume : public AEndSplineBrushVolume {
    GENERATED_BODY()
public:
    AEndNaviMapCaptureVolume(const FObjectInitializer& ObjectInitializer);

};

