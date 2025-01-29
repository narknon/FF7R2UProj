#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableSteeringGroup.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableSteeringGroup : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<uint8> GroupToAvoid_Array;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<uint8> GroupToIgnoreOverlap_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableSteeringGroup();
};

