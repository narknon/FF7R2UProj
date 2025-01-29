#pragma once
#include "CoreMinimal.h"
#include "EndTargetPoint.h"
#include "EndMovableTargetPoint.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndMovableTargetPoint : public AEndTargetPoint {
    GENERATED_BODY()
public:
    AEndMovableTargetPoint(const FObjectInitializer& ObjectInitializer);

};

