#pragma once
#include "CoreMinimal.h"
#include "EndNaviMapVolume.h"
#include "EndNaviMapVolumeGrid.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndNaviMapVolumeGrid : public AEndNaviMapVolume {
    GENERATED_BODY()
public:
    AEndNaviMapVolumeGrid(const FObjectInitializer& ObjectInitializer);

};

