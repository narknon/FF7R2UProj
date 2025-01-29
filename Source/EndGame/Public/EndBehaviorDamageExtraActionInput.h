#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EEndBattleDamageSourceHitReactionType.h"
#include "EndBehaviorDamageExtraActionInput.generated.h"

USTRUCT(BlueprintType)
struct FEndBehaviorDamageExtraActionInput {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndBattleDamageSourceHitReactionType DamageReactionType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bRotateToDamageVector;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector DamageVector;
    
    ENDGAME_API FEndBehaviorDamageExtraActionInput();
};

