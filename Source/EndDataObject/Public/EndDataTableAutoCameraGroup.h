#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableAutoCameraGroup.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableAutoCameraGroup : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 GroupType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> GroupMemberList_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableAutoCameraGroup();
};

