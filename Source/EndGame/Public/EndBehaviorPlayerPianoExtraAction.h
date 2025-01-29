#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorPianoExtraActionBase.h"
#include "EndBehaviorPlayerPianoExtraAction.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndBehaviorPlayerPianoExtraAction : public FEndBehaviorPianoExtraActionBase {
    GENERATED_BODY()
public:
    FEndBehaviorPlayerPianoExtraAction();
};

