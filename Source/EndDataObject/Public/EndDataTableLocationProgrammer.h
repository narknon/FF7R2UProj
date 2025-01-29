#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableLocationProgrammer.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableLocationProgrammer : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> EntryObjectList_Array;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName NextLocation;
    
public:
    ENDDATAOBJECT_API FEndDataTableLocationProgrammer();
};

