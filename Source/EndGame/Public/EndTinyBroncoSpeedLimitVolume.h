#pragma once
#include "CoreMinimal.h"
#include "EndVehicleSpeedLimitVolume.h"
#include "EndTinyBroncoSpeedLimitVolume.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndTinyBroncoSpeedLimitVolume : public AEndVehicleSpeedLimitVolume {
    GENERATED_BODY()
public:
    AEndTinyBroncoSpeedLimitVolume(const FObjectInitializer& ObjectInitializer);

};

