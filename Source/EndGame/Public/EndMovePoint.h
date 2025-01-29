#pragma once
#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "EndMovePoint.generated.h"

UCLASS(Blueprintable)
class AEndMovePoint : public ATargetPoint {
    GENERATED_BODY()
public:
    AEndMovePoint(const FObjectInitializer& ObjectInitializer);

};

