#pragma once
#include "CoreMinimal.h"
#include "EndWheeledVehicleSplineMoveActorBase.h"
#include "EndWheeledVehicleSplineMoveBattleEscape.generated.h"

UCLASS(Blueprintable, NotPlaceable)
class ENDGAME_API AEndWheeledVehicleSplineMoveBattleEscape : public AEndWheeledVehicleSplineMoveActorBase {
    GENERATED_BODY()
public:
    AEndWheeledVehicleSplineMoveBattleEscape(const FObjectInitializer& ObjectInitializer);

};

