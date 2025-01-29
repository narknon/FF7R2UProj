#pragma once
#include "CoreMinimal.h"
#include "EndBikePlayerEnemyDamageRatio.generated.h"

USTRUCT(BlueprintType)
struct FEndBikePlayerEnemyDamageRatio {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, float> EnemyDamageRatio;
    
    ENDGAME_API FEndBikePlayerEnemyDamageRatio();
};

