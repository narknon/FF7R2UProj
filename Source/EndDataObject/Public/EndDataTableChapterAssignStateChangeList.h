#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableChapterAssignStateChangeList.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableChapterAssignStateChangeList : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> AssignStateChange_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableChapterAssignStateChangeList();
};

