#pragma once
#include "CoreMinimal.h"
#include "EndCinemaDeformAnimParams.generated.h"

USTRUCT(BlueprintType)
struct FEndCinemaDeformAnimParams {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MeshPlacedLevel;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName MeshAccessorID;
    
    ENDGAME_API FEndCinemaDeformAnimParams();
};

