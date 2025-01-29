#pragma once
#include "CoreMinimal.h"
#include "Layout/Margin.h"
#include "EEndMenuAreaMapLOD.h"
#include "EndNaviMapLayerPrototypeDataV2.h"
#include "EndNaviMapLocationPrototypeDataV2.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndNaviMapLocationPrototypeDataV2 {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString Name;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString EnName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndNaviMapLayerPrototypeDataV2> layers;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MinPixelPerCm;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MidPixelPerCm;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MaxPixelPerCm;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMargin CursorAreaMargin;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndMenuAreaMapLOD ZoomMiddleLOD;
    
    FEndNaviMapLocationPrototypeDataV2();
};

