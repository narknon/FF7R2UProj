#pragma once
#include "CoreMinimal.h"
#include "EndSingleSidedSplineComponent.h"
#include "EndEnvironmentPhysicsSpawnSplineComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndEnvironmentPhysicsSpawnSplineComponent : public UEndSingleSidedSplineComponent {
    GENERATED_BODY()
public:
    UEndEnvironmentPhysicsSpawnSplineComponent(const FObjectInitializer& ObjectInitializer);

};

