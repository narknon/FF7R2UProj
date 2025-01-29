#pragma once
#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "EndFieldSplineMoveComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndFieldSplineMoveComponent : public USplineComponent {
    GENERATED_BODY()
public:
    UEndFieldSplineMoveComponent(const FObjectInitializer& ObjectInitializer);

};

