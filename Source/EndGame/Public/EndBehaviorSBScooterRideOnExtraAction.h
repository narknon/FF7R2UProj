#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorVehicleRideOnExtraActionBase.h"
#include "EndBehaviorSBScooterRideOnExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorSBScooterRideOnExtraAction : public FEndBehaviorVehicleRideOnExtraActionBase {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorSBScooterRideOnExtraAction();
};

