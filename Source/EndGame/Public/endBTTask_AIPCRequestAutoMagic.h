#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "endBTTask_AIPCRequestAutoMagic.generated.h"

UCLASS(Blueprintable)
class UendBTTask_AIPCRequestAutoMagic : public UBTTaskNode {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TimeOut;
    
    UendBTTask_AIPCRequestAutoMagic();

};

