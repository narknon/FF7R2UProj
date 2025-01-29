#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndGrassOffsetGridVisualizerComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndGrassOffsetGridVisualizerComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UEndGrassOffsetGridVisualizerComponent(const FObjectInitializer& ObjectInitializer);

};

