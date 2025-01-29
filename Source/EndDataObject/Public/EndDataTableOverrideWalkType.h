#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableOverrideWalkType.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableOverrideWalkType : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FString> OverrideWalkType_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableOverrideWalkType();
};

