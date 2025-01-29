#pragma once
#include "CoreMinimal.h"
#include "BoneControllers/AnimNode_SkeletalControlBase.h"
#include "AnimNode_EndPBD.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FAnimNode_EndPBD : public FAnimNode_SkeletalControlBase {
    GENERATED_BODY()
public:
    FAnimNode_EndPBD();
};

