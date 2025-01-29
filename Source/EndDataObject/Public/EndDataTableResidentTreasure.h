#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableResidentTreasure.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableResidentTreasure : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 UniqueIndex;
    
public:
    ENDDATAOBJECT_API FEndDataTableResidentTreasure();
};

