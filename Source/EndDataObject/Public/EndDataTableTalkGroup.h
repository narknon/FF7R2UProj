#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableTalkGroup.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableTalkGroup : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> TalkStateID_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableTalkGroup();
};

