#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTablePianoKeyboardBoneAssign.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTablePianoKeyboardBoneAssign : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> KeyBones_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTablePianoKeyboardBoneAssign();
};

