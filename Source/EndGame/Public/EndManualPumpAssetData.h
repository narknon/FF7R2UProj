#pragma once
#include "CoreMinimal.h"
#include "EndManualPumpAssetData.generated.h"

USTRUCT(BlueprintType)
struct FEndManualPumpAssetData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString AssetPath;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 LODs;
    
    ENDGAME_API FEndManualPumpAssetData();
};

