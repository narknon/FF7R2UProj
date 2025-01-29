#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EndBTTask_AIPCInfiniteCombo.generated.h"

UCLASS(Blueprintable)
class UEndBTTask_AIPCInfiniteCombo : public UBTTaskNode {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName InfiniteComboAbilityID;
    
    UEndBTTask_AIPCInfiniteCombo();

};

