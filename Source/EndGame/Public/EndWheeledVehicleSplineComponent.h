#pragma once
#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "EndWheeledVehicleSplineComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndWheeledVehicleSplineComponent : public USplineComponent {
    GENERATED_BODY()
public:
    UEndWheeledVehicleSplineComponent(const FObjectInitializer& ObjectInitializer);

};

