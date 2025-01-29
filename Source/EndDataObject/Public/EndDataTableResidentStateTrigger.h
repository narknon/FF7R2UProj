#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableResidentStateTrigger.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableResidentStateTrigger : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 UniqueIndex;
    
public:
    ENDDATAOBJECT_API FEndDataTableResidentStateTrigger();
};

