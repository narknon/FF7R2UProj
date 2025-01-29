#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableEventPriorityOverride.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableEventPriorityOverride : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<int32> Index_Array;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FString> OverrideProperty_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableEventPriorityOverride();
};

