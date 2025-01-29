#pragma once
#include "CoreMinimal.h"
#include "EndSingleSidedSplineComponent.h"
#include "EndVehicleDisableInOutSplineComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndVehicleDisableInOutSplineComponent : public UEndSingleSidedSplineComponent {
    GENERATED_BODY()
public:
    UEndVehicleDisableInOutSplineComponent(const FObjectInitializer& ObjectInitializer);

};

