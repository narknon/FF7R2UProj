#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNodeBase.h"
#include "Animation/AnimNodeBase.h"
#include "EndWheelExpressionBoneSetting.h"
#include "AnimNode_EndWheelExpression.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FAnimNode_EndWheelExpression : public FAnimNode_Base {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FPoseLink Source;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndWheelExpressionBoneSetting> BoneSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AccelerationRate;
    
    FAnimNode_EndWheelExpression();
};

