#pragma once
#include "CoreMinimal.h"
#include "EndBTDecorator_DurationBase.h"
#include "EndBTDecorator_AIPCDurationRequestGuard.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_AIPCDurationRequestGuard : public UEndBTDecorator_DurationBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool Inverse;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool IgnoreRedXIII;
    
    UEndBTDecorator_AIPCDurationRequestGuard();

};

