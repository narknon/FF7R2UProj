#pragma once
#include "CoreMinimal.h"
#include "Units/Highlevel/RigUnit_HighlevelBase.h"
#include "RigUnit_EndApplyAdditiveAnimation.generated.h"

USTRUCT(BlueprintType)
struct FRigUnit_EndApplyAdditiveAnimation : public FRigUnit_HighlevelBaseMutable {
    GENERATED_BODY()
public:
    ENDGAME_API FRigUnit_EndApplyAdditiveAnimation();
};

