#pragma once
#include "CoreMinimal.h"
#include "EndFieldActionCommonActorBase.h"
#include "EndFieldActionCloudSuppressActor.generated.h"

UCLASS(Abstract, Blueprintable)
class AEndFieldActionCloudSuppressActor : public AEndFieldActionCommonActorBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float InputDownSpeedRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float NoInputReverseSpeedRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DisableInputReverseSpeedRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TriggerEffectLeft;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TriggerEffectRight;
    
    AEndFieldActionCloudSuppressActor(const FObjectInitializer& ObjectInitializer);

};

