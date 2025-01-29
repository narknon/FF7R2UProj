#pragma once
#include "CoreMinimal.h"
#include "EndTargetPoint.h"
#include "EndBulletinBoardPoint.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndBulletinBoardPoint : public AEndTargetPoint {
    GENERATED_BODY()
public:
    AEndBulletinBoardPoint(const FObjectInitializer& ObjectInitializer);

};

