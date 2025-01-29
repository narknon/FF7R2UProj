#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SQEXSEADAutoSeComponentAssetTablePerSurface.generated.h"

USTRUCT(BlueprintType)
struct SQEXSEAD_API FSQEXSEADAutoSeComponentAssetTablePerSurface {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FSoftObjectPath SoundAssetPaths[8];
    
    FSQEXSEADAutoSeComponentAssetTablePerSurface();
};

