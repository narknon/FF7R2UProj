#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTablePlacement.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTablePlacement : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 UniqueIndex;
    
public:
    ENDDATAOBJECT_API FEndDataTablePlacement();
};

