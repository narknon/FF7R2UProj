#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableBikeCombo.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableBikeCombo : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> ComboID_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableBikeCombo();
};

