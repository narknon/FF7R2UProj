#pragma once
#include "CoreMinimal.h"
#include "EndBTDecorator_DurationBase.h"
#include "OverrideBattleParam.h"
#include "EndBTDecorator_AIPCDurationOverrideBattleParam.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_AIPCDurationOverrideBattleParam : public UEndBTDecorator_DurationBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FOverrideBattleParam Param;
    
    UEndBTDecorator_AIPCDurationOverrideBattleParam();

};

