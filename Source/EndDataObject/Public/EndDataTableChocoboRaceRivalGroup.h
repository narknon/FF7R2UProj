#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableChocoboRaceRivalGroup.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableChocoboRaceRivalGroup : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> RacerID_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableChocoboRaceRivalGroup();
};

