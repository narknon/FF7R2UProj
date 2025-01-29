#pragma once
#include "CoreMinimal.h"
#include "EndSimpleCameraWallVolume.h"
#include "EndFieldActionDamageReciveVolumeBase.generated.h"

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndFieldActionDamageReciveVolumeBase : public AEndSimpleCameraWallVolume {
    GENERATED_BODY()
public:
    AEndFieldActionDamageReciveVolumeBase(const FObjectInitializer& ObjectInitializer);

};

