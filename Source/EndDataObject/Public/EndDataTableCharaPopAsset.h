#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableCharaPopAsset.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableCharaPopAsset : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 UsedPhysMemory;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 UsedGPUMemory;
    
public:
    ENDDATAOBJECT_API FEndDataTableCharaPopAsset();
};

