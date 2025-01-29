#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndFieldActionCommonActorBase.h"
#include "EndFieldActionValveActor.generated.h"

class UEndFieldActionTriggerComponent;
class USoundBase;

UCLASS(Abstract, Blueprintable)
class AEndFieldActionValveActor : public AEndFieldActionCommonActorBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerComponent* TikableVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTransform PlayerTransform;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTransform IconTransform;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTransform HandleTransform;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 HandleRotCount;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USoundBase* ValveSoundBank;
    
public:
    AEndFieldActionValveActor(const FObjectInitializer& ObjectInitializer);

};

