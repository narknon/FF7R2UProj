#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EndBTTask_DoNothing.generated.h"

UCLASS(Blueprintable)
class UEndBTTask_DoNothing : public UBTTaskNode {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<EBTNodeResult::Type> m_SelectionType;
    
    UEndBTTask_DoNothing();

};

