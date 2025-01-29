#pragma once
#include "CoreMinimal.h"
#include "EndSplineBrushVolume.h"
#include "EndNaviMapModifierSubtractVolume.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class AEndNaviMapModifierSubtractVolume : public AEndSplineBrushVolume {
    GENERATED_BODY()
public:
    AEndNaviMapModifierSubtractVolume(const FObjectInitializer& ObjectInitializer);

};

