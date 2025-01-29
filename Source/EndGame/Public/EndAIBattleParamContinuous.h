#pragma once
#include "CoreMinimal.h"
#include "EndAIBattleParamBase.h"
#include "EndAIBattleParamContinuous.generated.h"

UCLASS(Blueprintable)
class UEndAIBattleParamContinuous : public UEndAIBattleParamBase {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ContinuousAttackTimeMax;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ContinuousAttackTimeMin;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AerialContinuousAttackTimeMax;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AerialContinuousAttackTimeMin;
    
    UEndAIBattleParamContinuous();

};

