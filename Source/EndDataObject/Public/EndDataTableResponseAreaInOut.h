#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableResponseAreaInOut.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableResponseAreaInOut : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Out2In;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName In2Out;
    
public:
    ENDDATAOBJECT_API FEndDataTableResponseAreaInOut();
};

