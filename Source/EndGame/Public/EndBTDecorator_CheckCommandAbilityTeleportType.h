#pragma once
#include "CoreMinimal.h"
#include "EEndBattleAbilityTeleportType.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_CheckCommandAbilityTeleportType.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_CheckCommandAbilityTeleportType : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndBattleAbilityTeleportType Type;
    
    UEndBTDecorator_CheckCommandAbilityTeleportType();

};

