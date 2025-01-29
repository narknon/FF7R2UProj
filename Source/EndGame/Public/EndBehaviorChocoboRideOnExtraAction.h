#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorVehicleRideOnExtraActionBase.h"
#include "EndBehaviorChocoboRideOnExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorChocoboRideOnExtraAction : public FEndBehaviorVehicleRideOnExtraActionBase {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorChocoboRideOnExtraAction();
};

