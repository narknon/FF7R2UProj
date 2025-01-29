#pragma once
#include "CoreMinimal.h"
#include "EndBattleAISummonBaseController.h"
#include "EndBattleAISU2020BaseController.generated.h"

UCLASS(Blueprintable)
class AEndBattleAISU2020BaseController : public AEndBattleAISummonBaseController {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> AbilitiesUseEmissive;
    
public:
    AEndBattleAISU2020BaseController(const FObjectInitializer& ObjectInitializer);

protected:
    UFUNCTION(BlueprintCallable)
    int32 GetIndexOfByAbilityId(FName AbilityId);
    
};

