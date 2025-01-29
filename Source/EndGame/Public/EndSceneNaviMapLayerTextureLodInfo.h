#pragma once
#include "CoreMinimal.h"
#include "EndSceneNaviMapLayerTextureInfo.h"
#include "EndSceneNaviMapLayerTextureLodInfo.generated.h"

USTRUCT(BlueprintType)
struct FEndSceneNaviMapLayerTextureLodInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float PixelPerCm;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndSceneNaviMapLayerTextureInfo> TextureInfos;
    
    ENDGAME_API FEndSceneNaviMapLayerTextureLodInfo();
};

