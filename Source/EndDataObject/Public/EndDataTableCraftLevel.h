#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableCraftLevel.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableCraftLevel : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 CraftExperienceValue;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 CraftLevel;
    
public:
    ENDDATAOBJECT_API FEndDataTableCraftLevel();
};

