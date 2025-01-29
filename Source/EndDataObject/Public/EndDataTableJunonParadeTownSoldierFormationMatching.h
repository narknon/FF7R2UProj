#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableJunonParadeTownSoldierFormationMatching.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableJunonParadeTownSoldierFormationMatching : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<uint8> PlatoonNumber_Array;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<uint8> PerformanceFormation_Array;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<uint8> PerformanceDifficulty_Array;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FString> PerformanceHelpText_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableJunonParadeTownSoldierFormationMatching();
};

