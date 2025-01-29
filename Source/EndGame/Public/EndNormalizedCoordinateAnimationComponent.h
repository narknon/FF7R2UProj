#pragma once
#include "CoreMinimal.h"
#include "EndCoordinateAnimationComponent.h"
#include "EndNormalizedCoordinateAnimationComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndNormalizedCoordinateAnimationComponent : public UEndCoordinateAnimationComponent {
    GENERATED_BODY()
public:
    UEndNormalizedCoordinateAnimationComponent(const FObjectInitializer& ObjectInitializer);

};

