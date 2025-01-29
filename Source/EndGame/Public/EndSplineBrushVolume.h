#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "EndSplineBrushVolume.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndSplineBrushVolume : public AVolume {
    GENERATED_BODY()
public:
    AEndSplineBrushVolume(const FObjectInitializer& ObjectInitializer);

};

