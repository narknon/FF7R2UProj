#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndNaviMapSilhouetteEdge.generated.h"

USTRUCT(BlueprintType)
struct FEndNaviMapSilhouetteEdge {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FVector> Vertices;
    
    ENDGAME_API FEndNaviMapSilhouetteEdge();
};

