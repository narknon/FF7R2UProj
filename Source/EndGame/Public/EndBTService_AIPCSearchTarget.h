#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "EndBTService_AIPCSearchTarget.generated.h"

UCLASS(Blueprintable)
class UEndBTService_AIPCSearchTarget : public UBTService {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool IgnoreAutoPlayUCPC;
    
    UEndBTService_AIPCSearchTarget();

};

