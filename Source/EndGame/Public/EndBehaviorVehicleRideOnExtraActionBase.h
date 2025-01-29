#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorVehicleRideOnExtraActionBase.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorVehicleRideOnExtraActionBase : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorVehicleRideOnExtraActionBase();
};

