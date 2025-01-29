#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndFieldRedHoldDeliverySetting.generated.h"

USTRUCT(BlueprintType)
struct FEndFieldRedHoldDeliverySetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString DamageSourceID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTransform TargetTransform;
    
    ENDGAME_API FEndFieldRedHoldDeliverySetting();
};

