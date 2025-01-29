#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTablePlayerTableFavPoint.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTablePlayerTableFavPoint : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 FavPoint;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> TargetPlayerTable_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTablePlayerTableFavPoint();
};

