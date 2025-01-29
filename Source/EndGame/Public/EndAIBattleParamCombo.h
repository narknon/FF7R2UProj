#pragma once
#include "CoreMinimal.h"
#include "EndAIBattleParamBase.h"
#include "EndAIBattleParamCombo.generated.h"

UCLASS(Blueprintable)
class UEndAIBattleParamCombo : public UEndAIBattleParamBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<float> ComboProbabilities;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<float> AerialComboProbabilities;
    
    UEndAIBattleParamCombo();

};

