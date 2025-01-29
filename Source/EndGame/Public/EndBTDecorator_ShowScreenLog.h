#pragma once
#include "CoreMinimal.h"
#include "EEndAIBTScreenLogType.h"
#include "EndBTDecorator_InvokeBase.h"
#include "EndBTDecorator_ShowScreenLog.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_ShowScreenLog : public UEndBTDecorator_InvokeBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndAIBTScreenLogType Type;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString Message;
    
    UEndBTDecorator_ShowScreenLog();

};

