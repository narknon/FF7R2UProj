#pragma once
#include "CoreMinimal.h"
#include "EndTargetPoint.h"
#include "EndCommunicationTowerPoint.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndCommunicationTowerPoint : public AEndTargetPoint {
    GENERATED_BODY()
public:
    AEndCommunicationTowerPoint(const FObjectInitializer& ObjectInitializer);

};

