#pragma once
#include "CoreMinimal.h"
#include "EndBikeAIControllerEnemyBase.h"
#include "EndBikeAISecuritySoldierSeniorController.generated.h"

UCLASS(Blueprintable)
class AEndBikeAISecuritySoldierSeniorController : public AEndBikeAIControllerEnemyBase {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> KeepLaneFreeOnWaves;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, float> LimitGrenadesOnWaves;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool CanSendLogGrenade;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName EntryTriggerName;
    
public:
    AEndBikeAISecuritySoldierSeniorController(const FObjectInitializer& ObjectInitializer);

};

