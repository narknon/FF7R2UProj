#pragma once
#include "CoreMinimal.h"
#include "EndVehicleCameraModule.h"
#include "EndChocoboRaceCameraModule.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndChocoboRaceCameraModule : public FEndVehicleCameraModule {
    GENERATED_BODY()
public:
    FEndChocoboRaceCameraModule();
};

