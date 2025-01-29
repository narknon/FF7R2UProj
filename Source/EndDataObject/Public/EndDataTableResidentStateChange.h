#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableResidentStateChange.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableResidentStateChange : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 UniqueIndex;
    
public:
    ENDDATAOBJECT_API FEndDataTableResidentStateChange();
};

