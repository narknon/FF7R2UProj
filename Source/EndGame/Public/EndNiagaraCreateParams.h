#pragma once
#include "CoreMinimal.h"
#include "VFXNiagaraCreateParams.h"
#include "EndNiagaraCreateParams.generated.h"

USTRUCT(BlueprintType)
struct FEndNiagaraCreateParams : public FVFXNiagaraCreateParams {
    GENERATED_BODY()
public:
    ENDGAME_API FEndNiagaraCreateParams();
};

