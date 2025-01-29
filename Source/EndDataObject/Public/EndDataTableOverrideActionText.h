#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableOverrideActionText.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableOverrideActionText : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TextId;
    
public:
    ENDDATAOBJECT_API FEndDataTableOverrideActionText();
};

