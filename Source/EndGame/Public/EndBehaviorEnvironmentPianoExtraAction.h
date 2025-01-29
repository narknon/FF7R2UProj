#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorPianoExtraActionBase.h"
#include "EndBehaviorEnvironmentPianoExtraAction.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndBehaviorEnvironmentPianoExtraAction : public FEndBehaviorPianoExtraActionBase {
    GENERATED_BODY()
public:
    FEndBehaviorEnvironmentPianoExtraAction();
};

