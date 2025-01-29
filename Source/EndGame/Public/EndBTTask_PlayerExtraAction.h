#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EndBTTask_PlayerExtraAction.generated.h"

UCLASS(Blueprintable)
class UEndBTTask_PlayerExtraAction : public UBTTaskNode {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ExtraActionName;
    
    UEndBTTask_PlayerExtraAction();

};

