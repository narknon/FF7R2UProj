#pragma once
#include "CoreMinimal.h"
#include "EConfrontType.h"
#include "EndBTDecorator_InvokeBase.h"
#include "EndBTDecorator_AIPCSetConfrontDistance.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_AIPCSetConfrontDistance : public UEndBTDecorator_InvokeBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EConfrontType ConfrontType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MinDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MaxDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Offset;
    
    UEndBTDecorator_AIPCSetConfrontDistance();

};

