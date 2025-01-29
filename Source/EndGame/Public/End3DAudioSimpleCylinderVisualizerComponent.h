#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "End3DAudioSimpleCylinderVisualizerComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEnd3DAudioSimpleCylinderVisualizerComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UEnd3DAudioSimpleCylinderVisualizerComponent(const FObjectInitializer& ObjectInitializer);

};

