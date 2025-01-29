#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableCondorFortMateria.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableCondorFortMateria : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AbilityId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName DamageSourceID;
    
public:
    ENDDATAOBJECT_API FEndDataTableCondorFortMateria();
};

