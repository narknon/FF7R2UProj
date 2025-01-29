#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableActionTest.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableActionTest : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 NaviBGMOff;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 NaviBGMOff2;
    
public:
    ENDDATAOBJECT_API FEndDataTableActionTest();
};

