#pragma once
#include "CoreMinimal.h"
#include "EndTargetPoint.h"
#include "EndBikeItemTargetPoint.generated.h"

UCLASS(Blueprintable)
class AEndBikeItemTargetPoint : public AEndTargetPoint {
    GENERATED_BODY()
public:
    AEndBikeItemTargetPoint(const FObjectInitializer& ObjectInitializer);

};

