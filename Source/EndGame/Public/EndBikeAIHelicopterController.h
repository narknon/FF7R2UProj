#pragma once
#include "CoreMinimal.h"
#include "EndBikeAIControllerEnemyBase.h"
#include "EndBikeAIHelicopterAbilitySet.h"
#include "EndBikeAIHelicopterAbilitySetPhase.h"
#include "EndBikeAIHelicopterFallEffectInfo.h"
#include "EndBikeAIHelicopterMoveParam_MoveAround.h"
#include "EndBikeAIHelicopterMoveParam_MoveBackward.h"
#include "EndBikeAIHelicopterMoveParam_MoveForward.h"
#include "EndBikeAIHelicopterParameter.h"
#include "EndBikeAIHelicopterSpecificRoadArea.h"
#include "EndBikeAIHelicopterController.generated.h"

UCLASS(Blueprintable)
class AEndBikeAIHelicopterController : public AEndBikeAIControllerEnemyBase {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndBikeAIHelicopterParameter mParameter;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, FEndBikeAIHelicopterMoveParam_MoveAround> MovementParams_MoveAround;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, FEndBikeAIHelicopterMoveParam_MoveForward> MovementParams_MoveForward;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, FEndBikeAIHelicopterMoveParam_MoveBackward> MovementParams_MoveBackward;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, FName> AbilityIDToMovementParams;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndBikeAIHelicopterAbilitySet AbilitySetForPlayer;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndBikeAIHelicopterAbilitySetPhase> AbilitySetForPlayer_Phase;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndBikeAIHelicopterSpecificRoadArea> RightRoadWallAreas;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndBikeAIHelicopterSpecificRoadArea> LeftRoadWallAreas;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndBikeAIHelicopterSpecificRoadArea> CenterObstacleAreas;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, FName> FocusAttacksOnWaves;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, float> LimitMissilesOnWaves;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float InterpSpeedScaleOnPlayerBoostAccel;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool CanSendLogMissile;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, FName> ExitVoiceOnWaves;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName FallTriggerName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndBikeAIHelicopterFallEffectInfo> FallEffectSettings;
    
public:
    AEndBikeAIHelicopterController(const FObjectInitializer& ObjectInitializer);

};

