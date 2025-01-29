#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableItemAnimalEscapeRoute.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableItemAnimalEscapeRoute : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SplineName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> PointName_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableItemAnimalEscapeRoute();
};

