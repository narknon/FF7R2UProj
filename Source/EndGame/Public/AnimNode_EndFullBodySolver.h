#pragma once
#include "CoreMinimal.h"
#include "BoneControllers/AnimNode_SkeletalControlBase.h"
#include "AnimNode_EndFullBodySolver.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FAnimNode_EndFullBodySolver : public FAnimNode_SkeletalControlBase {
    GENERATED_BODY()
public:
    FAnimNode_EndFullBodySolver();
};

