#pragma once
#include "CoreMinimal.h"
#include "EndTriggerVolume.h"
#include "EndCharaPopSwitchVolume.generated.h"

UCLASS(Blueprintable)
class AEndCharaPopSwitchVolume : public AEndTriggerVolume {
    GENERATED_BODY()
public:
    AEndCharaPopSwitchVolume(const FObjectInitializer& ObjectInitializer);

};

