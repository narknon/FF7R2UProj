#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableBattleEnemyIconUI.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableBattleEnemyIconUI : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Value;
    
public:
    ENDDATAOBJECT_API FEndDataTableBattleEnemyIconUI();
};

