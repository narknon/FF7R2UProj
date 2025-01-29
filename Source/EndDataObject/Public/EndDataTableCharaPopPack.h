#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableCharaPopPack.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableCharaPopPack : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> AssetName_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableCharaPopPack();
};

