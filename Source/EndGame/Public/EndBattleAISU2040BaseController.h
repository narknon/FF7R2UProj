#pragma once
#include "CoreMinimal.h"
#include "EndBattleAISummonBaseController.h"
#include "EndBattleAISU2040BaseController.generated.h"

UCLASS(Blueprintable)
class AEndBattleAISU2040BaseController : public AEndBattleAISummonBaseController {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<float> EmissiveChangeTimes;
    
public:
    AEndBattleAISU2040BaseController(const FObjectInitializer& ObjectInitializer);

protected:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnStartSummonCutSceneAbility();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnChangeLevel(int32 Level);
    
};

