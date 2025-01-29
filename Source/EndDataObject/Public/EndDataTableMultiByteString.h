#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableMultiByteString.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableMultiByteString : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString MultiByteString;
    
public:
    ENDDATAOBJECT_API FEndDataTableMultiByteString();
};

