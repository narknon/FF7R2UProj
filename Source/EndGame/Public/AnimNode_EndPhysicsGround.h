#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNodeBase.h"
#include "Animation/AnimNodeBase.h"
#include "AnimNode_EndPhysicsGround.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FAnimNode_EndPhysicsGround : public FAnimNode_Base {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FPoseLink Source;
    
    FAnimNode_EndPhysicsGround();
};

