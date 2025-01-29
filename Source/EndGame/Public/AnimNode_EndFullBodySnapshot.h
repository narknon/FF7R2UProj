#pragma once
#include "CoreMinimal.h"
#include "BoneControllers/AnimNode_SkeletalControlBase.h"
#include "AnimNode_EndFullBodySnapshot.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FAnimNode_EndFullBodySnapshot : public FAnimNode_SkeletalControlBase {
    GENERATED_BODY()
public:
    FAnimNode_EndFullBodySnapshot();
};

