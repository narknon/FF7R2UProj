#pragma once
#include "CoreMinimal.h"
#include "EndCameraModule.h"
#include "EndBattleOffsetModule.generated.h"

USTRUCT(BlueprintType)
struct FEndBattleOffsetModule : public FEndCameraModule {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBattleOffsetModule();
};

