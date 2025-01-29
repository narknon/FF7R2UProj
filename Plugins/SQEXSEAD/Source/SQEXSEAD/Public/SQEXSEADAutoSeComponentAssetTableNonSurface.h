#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SQEXSEADAutoSeComponentAssetTableNonSurface.generated.h"

USTRUCT(BlueprintType)
struct SQEXSEAD_API FSQEXSEADAutoSeComponentAssetTableNonSurface {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FSoftObjectPath SoundAssetPaths[14];
    
    FSQEXSEADAutoSeComponentAssetTableNonSurface();
};

