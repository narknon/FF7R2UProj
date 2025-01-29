#pragma once
#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "EndFieldMineCartSplineComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndFieldMineCartSplineComponent : public USplineComponent {
    GENERATED_BODY()
public:
    UEndFieldMineCartSplineComponent(const FObjectInitializer& ObjectInitializer);

};

