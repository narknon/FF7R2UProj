#pragma once
#include "CoreMinimal.h"
#include "EndNavMultiSwitchingVolume.h"
#include "EndNavSimpleMultiWallVolume.generated.h"

UCLASS(Blueprintable)
class AEndNavSimpleMultiWallVolume : public AEndNavMultiSwitchingVolume {
    GENERATED_BODY()
public:
    AEndNavSimpleMultiWallVolume(const FObjectInitializer& ObjectInitializer);

};

