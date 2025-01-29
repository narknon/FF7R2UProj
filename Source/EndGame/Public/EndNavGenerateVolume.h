#pragma once
#include "CoreMinimal.h"
#include "EndNavModifierVolumeBase.h"
#include "EndNavGenerateVolume.generated.h"

UCLASS(Blueprintable)
class AEndNavGenerateVolume : public AEndNavModifierVolumeBase {
    GENERATED_BODY()
public:
    AEndNavGenerateVolume(const FObjectInitializer& ObjectInitializer);

};

