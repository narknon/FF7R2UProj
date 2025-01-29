#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UEndBTTask_FindRelocationPoint.generated.h"

UCLASS(Blueprintable)
class UUEndBTTask_FindRelocationPoint : public UBTTaskNode {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName RelocationPointBlackBoardName;
    
    UUEndBTTask_FindRelocationPoint();

};

