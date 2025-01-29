#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableBattleCaitSithSlotReel.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableBattleCaitSithSlotReel : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<uint8> Pattern_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableBattleCaitSithSlotReel();
};

