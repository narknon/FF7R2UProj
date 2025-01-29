#pragma once
#include "CoreMinimal.h"
#include "EndFieldSimpleInteractPluginBehaviorBase.h"
#include "EndFieldSimpleInteractTargetTransSetting.h"
#include "EndFieldSimpleInteractPluginModifyTransform.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UEndFieldSimpleInteractPluginModifyTransform : public UEndFieldSimpleInteractPluginBehaviorBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndFieldSimpleInteractTargetTransSetting TargetSetting;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ModifyLocationLerpSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ModifyRotationLerpSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ModifyLocationInterpretSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ModifyRotationInterpretSpeed;
    
    UEndFieldSimpleInteractPluginModifyTransform();

};

