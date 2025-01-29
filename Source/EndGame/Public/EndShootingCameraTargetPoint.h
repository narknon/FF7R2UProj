#pragma once
#include "CoreMinimal.h"
#include "EndTargetPoint.h"
#include "EndShootingCameraTargetPoint.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndShootingCameraTargetPoint : public AEndTargetPoint {
    GENERATED_BODY()
public:
    AEndShootingCameraTargetPoint(const FObjectInitializer& ObjectInitializer);

};

