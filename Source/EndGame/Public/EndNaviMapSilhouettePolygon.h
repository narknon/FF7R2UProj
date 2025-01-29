#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndNaviMapSilhouettePolygon.generated.h"

USTRUCT(BlueprintType)
struct FEndNaviMapSilhouettePolygon {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Group;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector Vertices[3];
    
    ENDGAME_API FEndNaviMapSilhouettePolygon();
};

