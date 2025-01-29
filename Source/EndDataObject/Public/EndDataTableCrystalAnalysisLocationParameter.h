#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableCrystalAnalysisLocationParameter.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableCrystalAnalysisLocationParameter : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Bpm;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<int8> Note_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableCrystalAnalysisLocationParameter();
};

