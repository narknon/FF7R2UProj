#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EHSFLipSyncKeyframeMethod.h"
#include "HSFLipSyncSettings.generated.h"

UCLASS(Blueprintable, DefaultConfig, Config=Game)
class HSFLIPSYNCRUNTIME_API UHSFLipSyncSettings : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float Fps;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    EHSFLipSyncKeyframeMethod KeyframeMethod;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 StartOffset;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 EndOffset;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUseAudioPower;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bUseRandomization;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ExpressionLevel;
    
    UHSFLipSyncSettings();

};

