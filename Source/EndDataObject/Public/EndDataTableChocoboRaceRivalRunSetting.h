#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableChocoboRaceRivalRunSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableChocoboRaceRivalRunSetting : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<float> SectionTimeRate_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableChocoboRaceRivalRunSetting();
};

