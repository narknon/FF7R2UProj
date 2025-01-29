#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EndBTTask_RunWildPlayAction.generated.h"

UCLASS(Blueprintable)
class UEndBTTask_RunWildPlayAction : public UBTTaskNode {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SequenceName;
    
    UEndBTTask_RunWildPlayAction();

};

