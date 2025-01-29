#pragma once
#include "CoreMinimal.h"
#include "EndSplineBrushVolume.h"
#include "EndNaviMapModifierAddVolume.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class AEndNaviMapModifierAddVolume : public AEndSplineBrushVolume {
    GENERATED_BODY()
public:
    AEndNaviMapModifierAddVolume(const FObjectInitializer& ObjectInitializer);

};

