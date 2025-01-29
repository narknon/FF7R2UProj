#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndSceneNaviMapLayerTextureLodInfo.h"
#include "EndSceneNaviMapLayerInfo.generated.h"

USTRUCT(BlueprintType)
struct FEndSceneNaviMapLayerInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndSceneNaviMapLayerTextureLodInfo> TextureLods;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 LayerNumber;
    
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBox LayerBounds;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FBox LayerTextureBounds;
    
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> LayerVolumeNames;
    
    ENDGAME_API FEndSceneNaviMapLayerInfo();
};

