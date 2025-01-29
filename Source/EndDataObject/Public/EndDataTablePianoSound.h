#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTablePianoSound.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTablePianoSound : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 SoundType;
    
public:
    ENDDATAOBJECT_API FEndDataTablePianoSound();
};

