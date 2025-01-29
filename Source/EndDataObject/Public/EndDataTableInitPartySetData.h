#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableInitPartySetData.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableInitPartySetData : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> PlayerTableID_Array;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<uint8> PartySetPlayerStatus_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableInitPartySetData();
};

