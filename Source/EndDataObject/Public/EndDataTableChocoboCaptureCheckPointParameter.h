#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableChocoboCaptureCheckPointParameter.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableChocoboCaptureCheckPointParameter : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName RestartPoint;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<int32> SleepingVolumeIdxArray_Array;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ChocoboRestartPoint;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TroccoRestartPoint0;
    
public:
    ENDDATAOBJECT_API FEndDataTableChocoboCaptureCheckPointParameter();
};

