#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableCondorFortUnitParameter.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableCondorFortUnitParameter : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Health;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Attack;
    
public:
    ENDDATAOBJECT_API FEndDataTableCondorFortUnitParameter();
};

