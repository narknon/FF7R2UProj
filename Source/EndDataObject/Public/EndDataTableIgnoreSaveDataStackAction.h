#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableIgnoreSaveDataStackAction.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableIgnoreSaveDataStackAction : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 Option;
    
public:
    ENDDATAOBJECT_API FEndDataTableIgnoreSaveDataStackAction();
};

