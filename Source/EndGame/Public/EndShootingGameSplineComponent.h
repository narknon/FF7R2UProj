#pragma once
#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "EndShootingGameSplineComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndShootingGameSplineComponent : public USplineComponent {
    GENERATED_BODY()
public:
    UEndShootingGameSplineComponent(const FObjectInitializer& ObjectInitializer);

};

