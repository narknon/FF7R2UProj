#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EndBTTask_NeoBahamutSwitchToBlade.generated.h"

UCLASS(Blueprintable)
class UEndBTTask_NeoBahamutSwitchToBlade : public UBTTaskNode {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AbilityId;
    
    UEndBTTask_NeoBahamutSwitchToBlade();

};

