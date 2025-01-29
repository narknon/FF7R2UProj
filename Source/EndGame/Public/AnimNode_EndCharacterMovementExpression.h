#pragma once
#include "CoreMinimal.h"
#include "BoneControllers/AnimNode_SkeletalControlBase.h"
#include "AnimNode_EndCharacterMovementExpression.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FAnimNode_EndCharacterMovementExpression : public FAnimNode_SkeletalControlBase {
    GENERATED_BODY()
public:
    FAnimNode_EndCharacterMovementExpression();
};

