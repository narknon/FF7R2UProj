#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableCrashBoxForceAbility.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableCrashBoxForceAbility : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> ExcludeMateria_Array;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> ExcludeAbilityID_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableCrashBoxForceAbility();
};

