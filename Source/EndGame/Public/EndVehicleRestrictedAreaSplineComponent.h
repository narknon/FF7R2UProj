#pragma once
#include "CoreMinimal.h"
#include "EndSingleSidedSplineComponent.h"
#include "EndVehicleRestrictedAreaSplineComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndVehicleRestrictedAreaSplineComponent : public UEndSingleSidedSplineComponent {
    GENERATED_BODY()
public:
    UEndVehicleRestrictedAreaSplineComponent(const FObjectInitializer& ObjectInitializer);

};

