#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableCondorFortDeck.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableCondorFortDeck : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> UniqueUnitID_Array;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> UnitPresetID_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableCondorFortDeck();
};

