#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableActionGroup.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableActionGroup : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> ActionGroupLIst_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableActionGroup();
};

