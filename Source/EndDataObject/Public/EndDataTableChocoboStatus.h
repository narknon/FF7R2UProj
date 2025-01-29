#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableChocoboStatus.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableChocoboStatus : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 UniqueId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> HookNameArgument_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableChocoboStatus();
};

