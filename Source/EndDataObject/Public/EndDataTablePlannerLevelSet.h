#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTablePlannerLevelSet.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTablePlannerLevelSet : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> LevelList_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTablePlannerLevelSet();
};

