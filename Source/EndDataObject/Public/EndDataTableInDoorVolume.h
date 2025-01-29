#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableInDoorVolume.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableInDoorVolume : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float DashRootMotionTranslationScale;
    
public:
    ENDDATAOBJECT_API FEndDataTableInDoorVolume();
};

