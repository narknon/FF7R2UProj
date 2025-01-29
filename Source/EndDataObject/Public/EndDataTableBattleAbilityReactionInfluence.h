#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableBattleAbilityReactionInfluence.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableBattleAbilityReactionInfluence : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<uint8> ReactionInfluenceType_Array;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<uint8> AttackDirection_Array;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<uint8> PropertyCondition_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableBattleAbilityReactionInfluence();
};

