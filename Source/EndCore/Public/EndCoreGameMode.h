#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndCoreGameMode.generated.h"

UCLASS(Blueprintable, NonTransient)
class ENDCORE_API AEndCoreGameMode : public AGameModeBase {
    GENERATED_BODY()
public:
    AEndCoreGameMode(const FObjectInitializer& ObjectInitializer);

};

