#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableEnemyGil.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableEnemyGil : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<int32> Value_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableEnemyGil();
};

