#pragma once
#include "CoreMinimal.h"
#include "EndBattleAISummonBaseController.h"
#include "RageDush.h"
#include "EndBattleAISU0001BaseController.generated.h"

UCLASS(Blueprintable)
class AEndBattleAISU0001BaseController : public AEndBattleAISummonBaseController {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MoogleBombHoldingStartAnimation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MoogleBombHoldingIdleAnimation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FRageDush RageDushHandler;
    
    AEndBattleAISU0001BaseController(const FObjectInitializer& ObjectInitializer);

private:
    UFUNCTION(BlueprintCallable)
    void SetMoogleBombHidden(bool IsHidden);
    
};

