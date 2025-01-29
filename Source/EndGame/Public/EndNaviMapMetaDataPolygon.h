#pragma once
#include "CoreMinimal.h"
#include "EndNaviMapMetaDataVertex.h"
#include "EndNaviMapMetaDataPolygon.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndNaviMapMetaDataPolygon {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndNaviMapMetaDataVertex> verts;
    
    FEndNaviMapMetaDataPolygon();
};

