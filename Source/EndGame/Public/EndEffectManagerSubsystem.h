#pragma once
#include "CoreMinimal.h"
#include "EndEffectHandle.h"
#include "Subsystems/EngineSubsystem.h"
#include "VFXSoundElement.h"
#include "EndEffectManagerSubsystem.generated.h"

class UNiagaraComponent;
class UParticleSystemComponent;

UCLASS(Blueprintable)
class ENDGAME_API UEndEffectManagerSubsystem : public UEngineSubsystem {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    TMap<FEndEffectHandle, FVFXSoundElement> m_EffectToSoundElementMap;
    
public:
    UEndEffectManagerSubsystem();

    UFUNCTION(BlueprintCallable)
    void OnParticleSystemFinished(UParticleSystemComponent* FinishedComponent);
    
    UFUNCTION(BlueprintCallable)
    void OnNiagaraSystemFinished(UNiagaraComponent* FinishedComponent);
    
};

