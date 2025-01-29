#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableBattleCharaCategory.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableBattleCharaCategory : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 Category;
    
public:
    ENDDATAOBJECT_API FEndDataTableBattleCharaCategory();
};

