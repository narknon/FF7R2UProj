#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTablePlayerFavRank.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTablePlayerFavRank : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 NextFavPoint;
    
public:
    ENDDATAOBJECT_API FEndDataTablePlayerFavRank();
};

