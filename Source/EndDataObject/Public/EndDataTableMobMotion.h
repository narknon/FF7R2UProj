#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableMobMotion.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableMobMotion : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> MotionBindName_Array;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> MotionName_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableMobMotion();
};

