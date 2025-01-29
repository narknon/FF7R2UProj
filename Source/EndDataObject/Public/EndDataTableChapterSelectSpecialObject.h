#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableChapterSelectSpecialObject.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableChapterSelectSpecialObject : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 Type;
    
public:
    ENDDATAOBJECT_API FEndDataTableChapterSelectSpecialObject();
};

