#pragma once
#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "EndChocoboGlideGimmickSplineComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndChocoboGlideGimmickSplineComponent : public USplineComponent {
    GENERATED_BODY()
public:
    UEndChocoboGlideGimmickSplineComponent(const FObjectInitializer& ObjectInitializer);

};

