#pragma once
#include "CoreMinimal.h"
#include "EndFieldMovementSettingVolumeActor.h"
#include "EndFieldMovementSettingDisableOnlyNaviMoveVolumeActor.generated.h"

UCLASS(Blueprintable)
class AEndFieldMovementSettingDisableOnlyNaviMoveVolumeActor : public AEndFieldMovementSettingVolumeActor {
    GENERATED_BODY()
public:
    AEndFieldMovementSettingDisableOnlyNaviMoveVolumeActor(const FObjectInitializer& ObjectInitializer);

};

