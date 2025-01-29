#pragma once
#include "CoreMinimal.h"
#include "EndNiagaraCreateParams.h"
#include "EndCharacterResidentEffect.generated.h"

USTRUCT(BlueprintType)
struct FEndCharacterResidentEffect {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndNiagaraCreateParams m_NiagaraCreateParams;
    
    ENDGAME_API FEndCharacterResidentEffect();
};

