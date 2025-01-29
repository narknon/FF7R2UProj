#pragma once
#include "CoreMinimal.h"
#include "NiagaraActor.h"
#include "VFXNiagaraActor.generated.h"

UCLASS(Blueprintable)
class VFXNIAGARA_API AVFXNiagaraActor : public ANiagaraActor {
    GENERATED_BODY()
public:
    AVFXNiagaraActor(const FObjectInitializer& ObjectInitializer);

};

