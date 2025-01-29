#pragma once
#include "CoreMinimal.h"
#include "EEndBattlePlayerUniqueAbilityType.h"
#include "EndBTDecorator_CheckConditionBase.h"
#include "EndBTDecorator_CheckUniqueAbilityType.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_CheckUniqueAbilityType : public UEndBTDecorator_CheckConditionBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndBattlePlayerUniqueAbilityType Type;
    
    UEndBTDecorator_CheckUniqueAbilityType();

};

