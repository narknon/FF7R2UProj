#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTablePlannerEventVoiceList.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTablePlannerEventVoiceList : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Value;
    
public:
    ENDDATAOBJECT_API FEndDataTablePlannerEventVoiceList();
};

