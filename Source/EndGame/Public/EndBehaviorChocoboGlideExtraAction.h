#pragma once
#include "CoreMinimal.h"
#include "EndBehaviorExtraAction.h"
#include "EndBehaviorChocoboGlideExtraAction.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorChocoboGlideExtraAction : public FEndBehaviorExtraAction {
    GENERATED_BODY()
public:
    ENDGAME_API FEndBehaviorChocoboGlideExtraAction();
};

