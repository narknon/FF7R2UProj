#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Animation/AnimNodeBase.h"
#include "Animation/AnimNodeBase.h"
#include "EndChocoboExtraMovementExpressionNeckBoneSetting.h"
#include "EndChocoboExtraMovementExpressionNeckTurnSetting.h"
#include "AnimNode_EndChocoboExtraMovementExpression.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FAnimNode_EndChocoboExtraMovementExpression : public FAnimNode_Base {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FPoseLink Source;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnableNeckTurnExpression;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndChocoboExtraMovementExpressionNeckBoneSetting> BoneSettingArray;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndChocoboExtraMovementExpressionNeckTurnSetting JetActionSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndChocoboExtraMovementExpressionNeckTurnSetting GlideActionSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndChocoboExtraMovementExpressionNeckTurnSetting SliderActionSettings;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnablePenetrationControl;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float HeadMaxMoveSize;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float HipMaxMoveSize;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRotator HipRot;
    
public:
    FAnimNode_EndChocoboExtraMovementExpression();
};

