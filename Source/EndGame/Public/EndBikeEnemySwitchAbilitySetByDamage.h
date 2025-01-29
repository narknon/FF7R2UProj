#pragma once
#include "CoreMinimal.h"
#include "EndBikeEnemySwitchAbilitySetByDamage.generated.h"

USTRUCT(BlueprintType)
struct FEndBikeEnemySwitchAbilitySetByDamage {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Damage;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName BeforeAbilitySetId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AfterAbilitySetId;
    
    ENDGAME_API FEndBikeEnemySwitchAbilitySetByDamage();
};

