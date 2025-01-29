#pragma once
#include "CoreMinimal.h"
#include "EndSplineBrushComponent.h"
#include "EndSplineBrushHoleComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndSplineBrushHoleComponent : public UEndSplineBrushComponent {
    GENERATED_BODY()
public:
    UEndSplineBrushHoleComponent(const FObjectInitializer& ObjectInitializer);

};

