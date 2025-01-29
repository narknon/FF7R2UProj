#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableBattleConditionTriggerGroup.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableBattleConditionTriggerGroup : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> BattleConditionTriggerId_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableBattleConditionTriggerGroup();
};

