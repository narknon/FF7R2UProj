#pragma once
#include "CoreMinimal.h"
#include "AnimNodes/AnimNode_BlendSpacePlayer.h"
#include "EEndLocomotionState.h"
#include "EndLocomotionBlendSpacePlayerRotationRate.h"
#include "AnimNode_EndLocomotionBlendSpacePlayer.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FAnimNode_EndLocomotionBlendSpacePlayer : public FAnimNode_BlendSpacePlayer {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndLocomotionState LocomotionState;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndLocomotionBlendSpacePlayerRotationRate> RotationRateSettings;
    
    FAnimNode_EndLocomotionBlendSpacePlayer();
};

