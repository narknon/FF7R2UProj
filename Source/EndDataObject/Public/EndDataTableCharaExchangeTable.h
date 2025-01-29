#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableCharaExchangeTable.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableCharaExchangeTable : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString MotionFolder;
    
public:
    ENDDATAOBJECT_API FEndDataTableCharaExchangeTable();
};

