#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableLocationWork.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableLocationWork : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 LocationNumber;
    
public:
    ENDDATAOBJECT_API FEndDataTableLocationWork();
};

