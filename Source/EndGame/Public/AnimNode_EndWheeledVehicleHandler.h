#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNodeBase.h"
#include "Animation/AnimNodeBase.h"
#include "AnimNode_EndWheeledVehicleHandler.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FAnimNode_EndWheeledVehicleHandler : public FAnimNode_Base {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FPoseLink Source;
    
    FAnimNode_EndWheeledVehicleHandler();
};

