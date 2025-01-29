#pragma once
#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "EndFieldPlugCableSplineComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndFieldPlugCableSplineComponent : public USplineComponent {
    GENERATED_BODY()
public:
    UEndFieldPlugCableSplineComponent(const FObjectInitializer& ObjectInitializer);

};

