#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableFootAttribute.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableFootAttribute : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> EffectName_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableFootAttribute();
};

