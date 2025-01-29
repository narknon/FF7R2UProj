#pragma once
#include "CoreMinimal.h"
#include "BoneControllers/AnimNode_SkeletalControlBase.h"
#include "AnimNode_EndAdditiveDamage.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FAnimNode_EndAdditiveDamage : public FAnimNode_SkeletalControlBase {
    GENERATED_BODY()
public:
    FAnimNode_EndAdditiveDamage();
};

