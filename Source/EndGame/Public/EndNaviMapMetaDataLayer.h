#pragma once
#include "CoreMinimal.h"
#include "EndNaviMapMetaDataLayerBounds.h"
#include "EndNaviMapMetaDataLayer.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndNaviMapMetaDataLayer {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString Name;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 sort_order;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndNaviMapMetaDataLayerBounds bounds;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndNaviMapMetaDataLayerBounds volume_bounds;
    
    FEndNaviMapMetaDataLayer();
};

