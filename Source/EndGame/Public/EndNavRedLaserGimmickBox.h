#pragma once
#include "CoreMinimal.h"
#include "EndNavBlockingModifierVolume.h"
#include "EndNavRedLaserGimmickBox.generated.h"

UCLASS(Blueprintable)
class AEndNavRedLaserGimmickBox : public AEndNavBlockingModifierVolume {
    GENERATED_BODY()
public:
    AEndNavRedLaserGimmickBox(const FObjectInitializer& ObjectInitializer);

};

