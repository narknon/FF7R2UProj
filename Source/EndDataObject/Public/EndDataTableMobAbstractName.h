#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableMobAbstractName.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableMobAbstractName : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Index;
    
public:
    ENDDATAOBJECT_API FEndDataTableMobAbstractName();
};

