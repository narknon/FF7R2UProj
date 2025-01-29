#pragma once
#include "CoreMinimal.h"
#include "EndDataTableRowBase.h"
#include "EndDataTableBikePlayerFeedback.generated.h"

USTRUCT(BlueprintType)
struct FEndDataTableBikePlayerFeedback : public FEndDataTableRowBase {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName HitCameraShakeDataID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName HitForceFeedbackFileName;
    
public:
    ENDDATAOBJECT_API FEndDataTableBikePlayerFeedback();
};

