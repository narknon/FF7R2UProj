#pragma once
#include "CoreMinimal.h"
#include "EndNavBlockingModifierVolume.h"
#include "EndNavSimpleTerrainVolume.generated.h"

UCLASS(Blueprintable)
class AEndNavSimpleTerrainVolume : public AEndNavBlockingModifierVolume {
    GENERATED_BODY()
public:
    AEndNavSimpleTerrainVolume(const FObjectInitializer& ObjectInitializer);

};

