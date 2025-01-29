#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorWheeledVehicleDriverExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorWheeledVehicleDriverExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorWheeledVehicleDriverExtraAction();
};

