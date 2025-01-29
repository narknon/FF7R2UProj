#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndBattleAISummonBaseController.h"
#include "EndBattleAISU1000BaseController.generated.h"

UCLASS(Blueprintable)
class AEndBattleAISU1000BaseController : public AEndBattleAISummonBaseController {
    GENERATED_BODY()
public:
    AEndBattleAISU1000BaseController(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void SetHidePowerUpFX(bool bHide, bool bImmediately);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FVector GetLightningStrikeTargetLocation(int32 Index);
    
};

