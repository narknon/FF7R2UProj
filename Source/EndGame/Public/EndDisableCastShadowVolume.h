#pragma once
#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "EndDisableCastShadowVolume.generated.h"

UCLASS(Blueprintable)
class AEndDisableCastShadowVolume : public ATriggerVolume {
    GENERATED_BODY()
public:
    AEndDisableCastShadowVolume(const FObjectInitializer& ObjectInitializer);

};

