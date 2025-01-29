#pragma once
#include "CoreMinimal.h"
#include "AnimNotifyState_EndTimedNiagaraEffect.h"
#include "EndCurveParameterPair.h"
#include "AnimNotifyState_EndTimedNiagaraEffectAdvanced.generated.h"

class UMeshComponent;

UCLASS(Blueprintable, CollapseCategories, EditInlineNew)
class ENDGAME_API UAnimNotifyState_EndTimedNiagaraEffectAdvanced : public UAnimNotifyState_EndTimedNiagaraEffect {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bEnableNormalizedNotifyProgress;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName NotifyProgressUserParameter;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndCurveParameterPair> AnimCurves;
    
    UAnimNotifyState_EndTimedNiagaraEffectAdvanced();

    UFUNCTION(BlueprintCallable, BlueprintPure=false)
    float GetNotifyProgress(UMeshComponent* MeshComp) const;
    
};

