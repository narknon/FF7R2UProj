#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EEndAnimationCurveType.h"
#include "EEndTreasureAnimationPlayerType.h"
#include "EndAnimationSettingsAutoDisableLookAt.h"
#include "EndAnimationSettingsAutoSaccade.h"
#include "EndAnimationSettingsBattle.h"
#include "EndAnimationSettingsBlend.h"
#include "EndAnimationSettingsContact.h"
#include "EndAnimationSettingsFall.h"
#include "EndAnimationSettingsInput.h"
#include "EndAnimationSettingsLaunch.h"
#include "EndAnimationSettingsMovementExpression.h"
#include "EndAnimationSettingsPlannerEventCamera.h"
#include "EndAnimationSettingsReins.h"
#include "EndAnimationSettingsToroccoMiniGame.h"
#include "EndAnimationSettings.generated.h"

class UCurveFloat;

UCLASS(Blueprintable, DefaultConfig, Config=Game)
class ENDGAME_API UEndAnimationSettings : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAnimationSettingsInput Input;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAnimationSettingsBlend Blend;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAnimationSettingsFall Fall;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAnimationSettingsLaunch Launch;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAnimationSettingsBattle Battle;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAnimationSettingsContact Contact;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAnimationSettingsMovementExpression MovementExpression;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAnimationSettingsAutoSaccade AutoSaccade;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAnimationSettingsAutoDisableLookAt AutoDisableLookAt;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAnimationSettingsToroccoMiniGame ToroccoMinigame;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAnimationSettingsPlannerEventCamera> PlannerEventInCameraList;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, FEndAnimationSettingsPlannerEventCamera> PlannerEventInCameraTable;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndAnimationSettingsPlannerEventCamera PlannerEventOutCamera;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndAnimationSettingsReins> ReinsSettings;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<EEndAnimationCurveType, TSoftObjectPtr<UCurveFloat>> AnimationCurves;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BlendTimeMinWhenWaitMode;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TreasureBoxDistance;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TreasureBoxDistanceLR;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TreasureBoxPickUpDistance;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<EEndTreasureAnimationPlayerType, float> TreasureBoxPickUpDistanceMap;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TreasureBoxLocationSmoothingSpeed;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TreasureBoxRotationSmoothingSpeed;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TreasureBoxTurnTolerance;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TreasureBoxWalkRunEndWaitTime;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PushButtonLocationSmoothingSpeed;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PushButtonRotationSmoothingSpeed;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PushButtonTurnTolerance;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PushButtonWalkRunEndWaitTime;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FaceGuardLoopTimeMin;
    
    UEndAnimationSettings();

};

