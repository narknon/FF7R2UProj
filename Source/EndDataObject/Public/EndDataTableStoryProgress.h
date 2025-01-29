#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableStoryProgress.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableStoryProgress : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Progress;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 VoicePattern;
    
public:
    ENDDATAOBJECT_API FEndDataTableStoryProgress();
};

