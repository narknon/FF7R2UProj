#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableEnemyAP.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableEnemyAP : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<int32> Value_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableEnemyAP();
};

