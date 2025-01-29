#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableEnemyBookAreaData.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableEnemyBookAreaData : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString TextId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> LocationIDList_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableEnemyBookAreaData();
};

