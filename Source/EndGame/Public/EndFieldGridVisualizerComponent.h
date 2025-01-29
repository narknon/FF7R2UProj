#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndFieldGridVisualizerComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndFieldGridVisualizerComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UEndFieldGridVisualizerComponent(const FObjectInitializer& ObjectInitializer);

};

