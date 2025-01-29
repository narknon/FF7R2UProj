#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableChapterResetLocationWork.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableChapterResetLocationWork : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName LocationId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 LocationNumber;
    
public:
    ENDDATAOBJECT_API FEndDataTableChapterResetLocationWork();
};

