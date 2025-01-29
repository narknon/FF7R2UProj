#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WallPointData.generated.h"

USTRUCT(BlueprintType)
struct FWallPointData {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 Index;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector pos;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<uint32> neighborPointIndexes;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FVector Normal;
    
    ENDGAME_API FWallPointData();
};

