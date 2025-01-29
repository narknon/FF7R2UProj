#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableChocoboPartsColorPresetData.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableChocoboPartsColorPresetData : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<int32> ColorR_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableChocoboPartsColorPresetData();
};

