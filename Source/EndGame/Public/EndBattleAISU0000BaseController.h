#pragma once
#include "CoreMinimal.h"
#include "EndBattleAISummonBaseController.h"
#include "EndBattleAISU0000BaseController.generated.h"

UCLASS(Blueprintable)
class AEndBattleAISU0000BaseController : public AEndBattleAISummonBaseController {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ShoutAttackID;
    
    AEndBattleAISU0000BaseController(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void RequestShoutAttack();
    
};

