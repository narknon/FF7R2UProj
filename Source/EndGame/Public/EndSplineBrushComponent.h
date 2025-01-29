#pragma once
#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "EndSplineBrushComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndSplineBrushComponent : public USplineComponent {
    GENERATED_BODY()
public:
    UEndSplineBrushComponent(const FObjectInitializer& ObjectInitializer);

};

