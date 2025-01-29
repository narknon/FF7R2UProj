#pragma once
#include "CoreMinimal.h"
#include "ESQEXSEADANPlayAutoSeSourceType.h"
#include "ESQEXSEADAutoSeMotionSoundType.h"
#include "ESQEXSEADAutoSePartsType.h"
#include "SQEXSEADAnimNotifyPlayAutoSeParams.generated.h"

class USQEXSEADSurfaceAssetReferenceTable;

USTRUCT(BlueprintType)
struct SQEXSEAD_API FSQEXSEADAnimNotifyPlayAutoSeParams {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<ESQEXSEADANPlayAutoSeSourceType::Type> SourceType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<ESQEXSEADAutoSeMotionSoundType::Type> MotionSoundType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USQEXSEADSurfaceAssetReferenceTable* SurfaceAssetPathTable;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SurfaceAssetTableRecordName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TEnumAsByte<ESQEXSEADAutoSePartsType::Type> AutoSePartsType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 AutoSePartsIndex;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bCheckIsGrounded: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    uint8 bAttachToParts: 1;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SoundVolume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float SoundPitchMultiplier;
    
    FSQEXSEADAnimNotifyPlayAutoSeParams();
};

