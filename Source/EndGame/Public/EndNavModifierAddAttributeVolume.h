#pragma once
#include "CoreMinimal.h"
#include "EndNavModifierVolumeBase.h"
#include "EndNavModifierAddAttributeVolume.generated.h"

UCLASS(Blueprintable)
class AEndNavModifierAddAttributeVolume : public AEndNavModifierVolumeBase {
    GENERATED_BODY()
public:
    AEndNavModifierAddAttributeVolume(const FObjectInitializer& ObjectInitializer);

};

