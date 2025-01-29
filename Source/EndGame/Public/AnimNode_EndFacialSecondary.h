#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNodeBase.h"
#include "AnimNode_HSFLipSync.h"
#include "AnimNode_EndFacialSecondary.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FAnimNode_EndFacialSecondary : public FAnimNode_HSFLipSync {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FPoseLink Source;
    
    FAnimNode_EndFacialSecondary();
};

