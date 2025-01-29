#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableChocoboRaceParameterLevel.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableChocoboRaceParameterLevel : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<int8> Level_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableChocoboRaceParameterLevel();
};

