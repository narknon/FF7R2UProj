#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EEnd3DAudioActorUseType.h"
#include "End3DAudioSimpleCylinder.h"
#include "End3DAudioTriggerRequest.h"
#include "End3DAudioActor.generated.h"

class USoundAttenuation;

UCLASS(Blueprintable)
class ENDGAME_API AEnd3DAudioActor : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEnd3DAudioSimpleCylinder _rangeForUI;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEnd3DAudioSimpleCylinder _rangeForReset;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName _jbId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float _autoPlayDist;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEnd3DAudioActorUseType _useType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName _stateChangeObjectId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName _playStopStateId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName _zerooneStateChangeObjectId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName _setZerooneEnableStateId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USoundAttenuation* _overwriteAttenuationSetting;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEnd3DAudioTriggerRequest> _triggerRequest;
    
    AEnd3DAudioActor(const FObjectInitializer& ObjectInitializer);

};

