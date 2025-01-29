#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataAsset.h"
#include "EndVehicleAutoRideParam.h"
#include "EndWheeledSafeAreaCheckerParam.h"
#include "EndWheeledVehicleActionAppearCameraParam.h"
#include "EndWheeledVehicleActionAppearParam.h"
#include "EndWheeledVehicleAttackParam.h"
#include "EndWheeledVehicleBattleEscapeParam.h"
#include "EndWheeledVehicleMovementInRestrictedAreaParam.h"
#include "EndWheeledVehicleMovementWaterRestrictionParam.h"
#include "EndWheeledVehicleRespawnAfterBattleParam.h"
#include "EndWheeledVehicleRiderReactionParam.h"
#include "EndWheeledVehicleSpawnableAreaData.h"
#include "EndWheeledVehicleStuckCheckParam.h"
#include "EndWheeledVehicleWorldItemCollectParam.h"
#include "EndWheeledVehicleActionParams.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API UEndWheeledVehicleActionParams : public UDataAsset {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndWheeledVehicleActionAppearParam AppearParam;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndWheeledVehicleActionAppearCameraParam AppearCameraParam;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndWheeledVehicleSpawnableAreaData SpawnableAreaData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndWheeledVehicleWorldItemCollectParam WorldItemCollectParam;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndWheeledVehicleMovementInRestrictedAreaParam RestrictedAreaParam;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndWheeledVehicleMovementWaterRestrictionParam WaterRestrictionParam;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector AISteeringOverrideObstacleExtent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector AISteeringOverrideObstacleOffset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndWheeledSafeAreaCheckerParam SafeAreaCheckerParam;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndWheeledVehicleBattleEscapeParam EscapeParam;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndVehicleAutoRideParam AutoRideParam;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndWheeledVehicleStuckCheckParam StuckCheckParam;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndWheeledVehicleAttackParam AttackParam;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndWheeledVehicleRiderReactionParam RiderReactionParam;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndWheeledVehicleRespawnAfterBattleParam RespawnAfterBattleParam;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector CameraFollowOffset;
    
    UEndWheeledVehicleActionParams();

};

