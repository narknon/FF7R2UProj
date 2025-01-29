#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableCardGameCardInfl.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableCardGameCardInfl : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 Column1;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 Column2;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 Column3;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 Column4;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    int8 Column5;
    
public:
    ENDDATAOBJECT_API FEndDataTableCardGameCardInfl();
};

