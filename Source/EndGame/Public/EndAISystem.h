#pragma once
#include "CoreMinimal.h"
#include "AISystem.h"
#include "UObject/NoExportTypes.h"
#include "EEndAIState.h"
#include "EndAISystem.generated.h"

class UBehaviorTree;
class UEndAIBattlePlayerAutoMagicInfo;
class UEndAIControllerManager;
class UEnvQuery;
class UObject;

UCLASS(Blueprintable, Config=Game)
class UEndAISystem : public UAISystem {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    UEndAIControllerManager* ControllerManager;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    UEndAIBattlePlayerAutoMagicInfo* AutoMagicInfo;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AIMoveCorrectEdgeMergin;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AIMoveCorrectEdgeMaxRatio;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AIMoveCorneringDistance;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AIMoveRouteInterpSlopeRatio;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AsyncNavProcessingAllowableTime;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AsyncNavProcessingAllowableTimeLong;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<EEndAIState> AIStatesInterestedByAnimals;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSoftClassPath AutoMagicInfoPath;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<UObject*> DangerSourceList;
    
public:
    UEndAISystem(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    static void LoadBehaviorTreeAsset(UBehaviorTree* Asset);
    
    UFUNCTION(BlueprintCallable)
    static void ClearEQSAssetCache(UEnvQuery* Asset);
    
    UFUNCTION(BlueprintCallable)
    static void ClearBehaviorTreeAssetCache(UBehaviorTree* Asset);
    
};

