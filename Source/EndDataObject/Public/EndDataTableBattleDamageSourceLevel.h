#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableBattleDamageSourceLevel.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableBattleDamageSourceLevel : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FString> TakeDamageActorName_Array;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FString> TakeDamageStateTrigger_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableBattleDamageSourceLevel();
};

