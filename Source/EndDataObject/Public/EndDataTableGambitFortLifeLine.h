#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableGambitFortLifeLine.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableGambitFortLifeLine : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName LineSourceName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName LineTargetName;
    
public:
    ENDDATAOBJECT_API FEndDataTableGambitFortLifeLine();
};

