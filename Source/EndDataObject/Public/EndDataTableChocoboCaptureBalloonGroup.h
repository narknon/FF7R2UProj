#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableChocoboCaptureBalloonGroup.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableChocoboCaptureBalloonGroup : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<uint8> PhaseAction_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableChocoboCaptureBalloonGroup();
};

