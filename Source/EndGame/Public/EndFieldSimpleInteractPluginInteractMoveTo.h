#pragma once
#include "CoreMinimal.h"
#include "EndFieldSimpleInteractPluginBase.h"
#include "EndFieldSimpleInteractTargetTransSetting.h"
#include "EndFieldSimpleInteractPluginInteractMoveTo.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndFieldSimpleInteractPluginInteractMoveTo : public UEndFieldSimpleInteractPluginBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndFieldSimpleInteractTargetTransSetting TargetSetting;
    
    UEndFieldSimpleInteractPluginInteractMoveTo();

};

