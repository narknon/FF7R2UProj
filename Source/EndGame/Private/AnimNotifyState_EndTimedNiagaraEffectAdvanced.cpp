#include "AnimNotifyState_EndTimedNiagaraEffectAdvanced.h"

UAnimNotifyState_EndTimedNiagaraEffectAdvanced::UAnimNotifyState_EndTimedNiagaraEffectAdvanced() {
    this->bEnableNormalizedNotifyProgress = false;
    this->NotifyProgressUserParameter = TEXT("NormalizedNotifyProgress");
}

float UAnimNotifyState_EndTimedNiagaraEffectAdvanced::GetNotifyProgress(UMeshComponent* MeshComp) const {
    return 0.0f;
}


