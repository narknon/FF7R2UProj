#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNodeBase.h"
#include "Animation/AnimNodeBase.h"
#include "EndVelocityExpressionBoneSetting.h"
#include "AnimNode_EndVelocityExpression.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FAnimNode_EndVelocityExpression : public FAnimNode_Base {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FPoseLink Source;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndVelocityExpressionBoneSetting> BoneSettings;
    
    FAnimNode_EndVelocityExpression();
};

