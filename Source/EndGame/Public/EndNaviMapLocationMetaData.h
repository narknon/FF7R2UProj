#pragma once
#include "CoreMinimal.h"
#include "EndNaviMapMetaDataActor.h"
#include "EndNaviMapMetaDataLayer.h"
#include "EndNaviMapLocationMetaData.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndNaviMapLocationMetaData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FString Name;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 scene_layer;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndNaviMapMetaDataActor> Actors;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndNaviMapMetaDataLayer> layers;
    
    FEndNaviMapLocationMetaData();
};

