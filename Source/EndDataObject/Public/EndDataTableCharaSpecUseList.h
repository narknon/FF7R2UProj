#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableCharaSpecUseList.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableCharaSpecUseList : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName UseCharaSpec;
    
public:
    ENDDATAOBJECT_API FEndDataTableCharaSpecUseList();
};

