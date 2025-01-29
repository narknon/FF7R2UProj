#pragma once
#include "CoreMinimal.h"
#include "BoneControllers/AnimNode_SkeletalControlBase.h"
#include "AnimNode_EndCopyBoneTransforms.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FAnimNode_EndCopyBoneTransforms : public FAnimNode_SkeletalControlBase {
    GENERATED_BODY()
public:
    FAnimNode_EndCopyBoneTransforms();
};

