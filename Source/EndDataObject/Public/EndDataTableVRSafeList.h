#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableVRSafeList.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableVRSafeList : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SafeList;
    
public:
    ENDDATAOBJECT_API FEndDataTableVRSafeList();
};

