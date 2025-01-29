#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableEnemyBookBattleAbility.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableEnemyBookBattleAbility : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString Name;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString ReplaceDamageSourceID;
    
public:
    ENDDATAOBJECT_API FEndDataTableEnemyBookBattleAbility();
};

