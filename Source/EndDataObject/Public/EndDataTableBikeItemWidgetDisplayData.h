#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableBikeItemWidgetDisplayData.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableBikeItemWidgetDisplayData : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> SplineName_Array;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<float> InputKey_Array;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<int32> LapNumber_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableBikeItemWidgetDisplayData();
};

