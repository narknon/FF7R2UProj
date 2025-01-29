#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableEmotion.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableEmotion : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 CanUpperBodyAnimation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FString> MotionName_Array;
    
public:
    ENDDATAOBJECT_API FEndDataTableEmotion();
};

