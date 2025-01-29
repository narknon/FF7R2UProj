#pragma once
#include "CoreMinimal.h"
#include "EndFieldMovementSettingVolumeActor.h"
#include "EndMochFieldActionVolumeActor.generated.h"

UCLASS(Blueprintable)
class AEndMochFieldActionVolumeActor : public AEndFieldMovementSettingVolumeActor {
    GENERATED_BODY()
public:
    AEndMochFieldActionVolumeActor(const FObjectInitializer& ObjectInitializer);

};

