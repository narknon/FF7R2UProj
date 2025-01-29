#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableBattleCombinationTable.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableBattleCombinationTable : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> CombinationAbilityID_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableBattleCombinationTable();
};

