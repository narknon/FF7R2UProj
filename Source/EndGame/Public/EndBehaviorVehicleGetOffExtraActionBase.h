#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorVehicleGetOffExtraActionBase.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorVehicleGetOffExtraActionBase : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorVehicleGetOffExtraActionBase();
};

