#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNode_SequencePlayer.h"
#include "EEndLocomotionState.h"
#include "EndLocomotionSequencePlayerRotationRate.h"
#include "AnimNode_EndLocomotionSequencePlayer.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FAnimNode_EndLocomotionSequencePlayer : public FAnimNode_SequencePlayer {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndLocomotionState LocomotionState;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndLocomotionSequencePlayerRotationRate> RotationRateSettings;
    
    FAnimNode_EndLocomotionSequencePlayer();
};

