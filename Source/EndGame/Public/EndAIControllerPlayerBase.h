#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "EAIPCAttackKind.h"
#include "EndAIAttackKindBattleParams.h"
#include "EndAIControllerBluePrintBase.h"
#include "EndBattleAITargetChoosingParam.h"
#include "Templates/SubclassOf.h"
#include "EndAIControllerPlayerBase.generated.h"

class AEndCharacter;
class UEndAIBattleParamBase;
class UEnvQuery;

UCLASS(Blueprintable, MinimalAPI)
class AEndAIControllerPlayerBase : public AEndAIControllerBluePrintBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UEnvQuery* MountSpawnEQS;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndBattleAITargetChoosingParam TargetChoosingParam;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float GroundTargetReachableHeight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AirTargetReachableHeight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float GroundTargetReachableHeightRangedWeapon;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AirTargetReachableHeightRangedWeapon;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TeleportAbilityId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> ContinueOffensiveModeAbilityIdList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<EAIPCAttackKind, FEndAIAttackKindBattleParams> BattleParams;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<UEndAIBattleParamBase> ToadBattleParam;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float StandbyTimeMax;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float StandbyTimeMin;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DangerDamagerSensorRadiusCoe;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float OcclusionTestSphereRadius;
    
public:
    AEndAIControllerPlayerBase(const FObjectInitializer& ObjectInitializer);

private:
    UFUNCTION(BlueprintCallable)
    static void TestResetAI(AEndCharacter* InCharacter);
    
    UFUNCTION(BlueprintCallable)
    void TestMoveTo(FVector TargetLocation, bool bFindPath);
    
    UFUNCTION(BlueprintCallable)
    static void TestJumpToWall(AEndCharacter* InCharacter, FVector TargetLocation, FVector UpVector);
    
    UFUNCTION(BlueprintCallable)
    static void TestJumpToGround(AEndCharacter* InCharacter, FTransform TargetTransform);
    
    UFUNCTION(BlueprintCallable)
    void TestAIJumpToWall(FTransform TargetTransform);
    
    UFUNCTION(BlueprintCallable)
    void TestAIJumpToGround(FTransform TargetTransform);
    
};

