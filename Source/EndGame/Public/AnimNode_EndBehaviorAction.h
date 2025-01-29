#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNodeBase.h"
#include "Animation/AnimNodeBase.h"
#include "AnimNode_EndBehaviorAction.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FAnimNode_EndBehaviorAction : public FAnimNode_Base {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FPoseLink Source;
    
    FAnimNode_EndBehaviorAction();
};

