#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableQuestObject.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableQuestObject : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> ObjectID_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableQuestObject();
};

