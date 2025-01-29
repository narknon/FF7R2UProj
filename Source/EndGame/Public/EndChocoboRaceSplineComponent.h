#pragma once
#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "EndChocoboRaceSplineComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndChocoboRaceSplineComponent : public USplineComponent {
    GENERATED_BODY()
public:
    UEndChocoboRaceSplineComponent(const FObjectInitializer& ObjectInitializer);

};

