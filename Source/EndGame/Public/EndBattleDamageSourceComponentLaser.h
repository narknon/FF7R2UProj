#pragma once
#include "CoreMinimal.h"
#include "EndBattleDamageSourceComponentTraceHit.h"
#include "EndBattleDamageSourceComponentLaser.generated.h"

class UParticleSystemComponent;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBattleDamageSourceComponentLaser : public UEndBattleDamageSourceComponentTraceHit {
    GENERATED_BODY()
public:
    UEndBattleDamageSourceComponentLaser(const FObjectInitializer& ObjectInitializer);

private:
    UFUNCTION(BlueprintCallable)
    void OnBindEffectFinished(UParticleSystemComponent* FinishedComponent);
    
};

