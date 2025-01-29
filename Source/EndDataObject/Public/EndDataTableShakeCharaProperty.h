#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableShakeCharaProperty.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableShakeCharaProperty : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName CameraShakeDataID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ForceFeedbackFileName;
    
public:
    ENDDATAOBJECT_API FEndDataTableShakeCharaProperty();
};

