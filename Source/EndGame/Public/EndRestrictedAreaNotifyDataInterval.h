#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndRestrictedAreaNotifyData.h"
#include "EndRestrictedAreaNotifyDataInterval.generated.h"

USTRUCT(BlueprintType)
struct FEndRestrictedAreaNotifyDataInterval {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndRestrictedAreaNotifyData NotifyData;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FFloatInterval AppliedRange;
    
    ENDGAME_API FEndRestrictedAreaNotifyDataInterval();
};

