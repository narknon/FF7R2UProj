#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SQEXSEADSurfaceAssetReferenceRecord.generated.h"

USTRUCT(BlueprintType)
struct SQEXSEAD_API FSQEXSEADSurfaceAssetReferenceRecord {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName Name;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FSoftObjectPath AssetRefs[63];
    
    FSQEXSEADSurfaceAssetReferenceRecord();
};

