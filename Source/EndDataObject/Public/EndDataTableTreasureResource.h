#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableTreasureResource.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableTreasureResource : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName EffectResourceName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName EffectAttachSocketName;
    
public:
    ENDDATAOBJECT_API FEndDataTableTreasureResource();
};

