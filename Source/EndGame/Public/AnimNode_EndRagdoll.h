#pragma once
#include "CoreMinimal.h"
#include "BoneControllers/AnimNode_SkeletalControlBase.h"
#include "AnimNode_EndRagdoll.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FAnimNode_EndRagdoll : public FAnimNode_SkeletalControlBase {
    GENERATED_BODY()
public:
    FAnimNode_EndRagdoll();
};

