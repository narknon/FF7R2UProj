#pragma once
#include "CoreMinimal.h"
#include "HSFLipSyncInput.generated.h"

class UHSFLipSyncDataPack;

USTRUCT(BlueprintType)
struct HSFLIPSYNCRUNTIME_API FHSFLipSyncInput {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UHSFLipSyncDataPack* Pack;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName KeyName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MappingName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float EvaluateTime;
    
    FHSFLipSyncInput();
};

