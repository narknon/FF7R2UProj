#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_VFXTimedNiagaraEffect.generated.h"

UCLASS(Abstract, Blueprintable, CollapseCategories, EditInlineNew)
class VFXNIAGARA_API UAnimNotifyState_VFXTimedNiagaraEffect : public UAnimNotifyState {
    GENERATED_BODY()
public:
    UAnimNotifyState_VFXTimedNiagaraEffect();

};

