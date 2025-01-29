#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndMenuWorldMapAreaSetting.generated.h"

USTRUCT(BlueprintType)
struct FEndMenuWorldMapAreaSetting {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSoftObjectPath ThumbnailImage;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString FlavorText;
    
    ENDGAME_API FEndMenuWorldMapAreaSetting();
};

