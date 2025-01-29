#pragma once
#include "CoreMinimal.h"
#include "EndBikeDamageSourceComponent.h"
#include "EndBikeDamageSourceComponentLaser.generated.h"

class UParticleSystemComponent;

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBikeDamageSourceComponentLaser : public UEndBikeDamageSourceComponent {
    GENERATED_BODY()
public:
    UEndBikeDamageSourceComponentLaser(const FObjectInitializer& ObjectInitializer);

private:
    UFUNCTION(BlueprintCallable)
    void OnBindEffectFinished(UParticleSystemComponent* FinishedComponent);
    
};

