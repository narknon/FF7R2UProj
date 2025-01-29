#pragma once
#include "CoreMinimal.h"
#include "EAIPCBattleParamType.h"
#include "Templates/SubclassOf.h"
#include "EndAIAttackKindBattleParams.generated.h"

class UEndAIBattleParamBase;

USTRUCT(BlueprintType)
struct FEndAIAttackKindBattleParams {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<EAIPCBattleParamType, TSubclassOf<UEndAIBattleParamBase>> BattleParams;
    
    ENDGAME_API FEndAIAttackKindBattleParams();
};

