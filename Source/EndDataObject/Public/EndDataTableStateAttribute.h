#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableStateAttribute.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableStateAttribute : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 AttributeIndex;
    
public:
    ENDDATAOBJECT_API FEndDataTableStateAttribute();
};

