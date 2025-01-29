#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableEnemyEXP.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableEnemyEXP : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<int32> Value_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableEnemyEXP();
};

