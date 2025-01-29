#pragma once
#include "CoreMinimal.h"
#include "EndMenuPlayerImageSetting.h"
#include "EndMenuPlayerOverrideImageSetting.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndMenuPlayerOverrideImageSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName StoryFlag;
    
    UPROPERTY(BlueprintReadWrite, Config, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndMenuPlayerImageSetting Images;
    
    FEndMenuPlayerOverrideImageSetting();
};

