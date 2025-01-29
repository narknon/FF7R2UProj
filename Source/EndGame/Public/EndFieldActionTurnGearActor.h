#pragma once
#include "CoreMinimal.h"
#include "EndFieldActionCommonActorBase.h"
#include "EndFieldActionTurnGearActor.generated.h"

class UEndFieldActionTriggerComponent;
class USoundBase;

UCLASS(Abstract, Blueprintable)
class AEndFieldActionTurnGearActor : public AEndFieldActionCommonActorBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndFieldActionTriggerComponent* TikableVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TurnAngleMax;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TurnAngleMaxTriggerName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PlayerMotionSpeedUpStartSec;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PlayerMotionSpeedUpStartToMaxSec;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PlayerMotionSpeedUpMaxRate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName LifeStreamSelectTargetPointName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USoundBase* SoundBank_Turning;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USoundBase* SoundBank_LifeStream;
    
public:
    AEndFieldActionTurnGearActor(const FObjectInitializer& ObjectInitializer);

};

