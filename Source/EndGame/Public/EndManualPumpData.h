#pragma once
#include "CoreMinimal.h"
#include "EndManualPumpAssetData.h"
#include "EndManualPumpData.generated.h"

USTRUCT(BlueprintType)
struct FEndManualPumpData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 ManualCutIndex;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndManualPumpAssetData> ManualAssetInfos;
    
    ENDGAME_API FEndManualPumpData();
};

