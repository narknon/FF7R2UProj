#pragma once
#include "CoreMinimal.h"
#include "AnimNotifyState_TimedNiagaraEffect.h"
#include "EEndTimedNiagaraEffectAdvanced_CurveParameterType.h"
#include "EndCurveParameterPair.generated.h"

USTRUCT(BlueprintType)
struct FEndCurveParameterPair : public FCurveParameterPair {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndTimedNiagaraEffectAdvanced_CurveParameterType m_CurveParameterType;
    
    ENDGAME_API FEndCurveParameterPair();
};

