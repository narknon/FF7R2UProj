#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableChocoboCraftLocationSaveParameter.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableChocoboCraftLocationSaveParameter : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 SaveDataArrayIndex;
    
public:
    ENDDATAOBJECT_API FEndDataTableChocoboCraftLocationSaveParameter();
};

