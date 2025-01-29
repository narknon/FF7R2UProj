#pragma once
#include "CoreMinimal.h"
#include "EndAIDangerSourceInterface.h"
#include "EndBattleDamageSourceComponent.h"
#include "EndBattleDamageSourceComponentTraceHit.generated.h"

class AEndDynamicBodyCollisionActor;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBattleDamageSourceComponentTraceHit : public UEndBattleDamageSourceComponent, public IEndAIDangerSourceInterface {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    AEndDynamicBodyCollisionActor* PushCollisionActor;
    
public:
    UEndBattleDamageSourceComponentTraceHit(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

