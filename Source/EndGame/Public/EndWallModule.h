#pragma once
#include "CoreMinimal.h"
#include "EndWallModule.generated.h"

USTRUCT(BlueprintType)
struct ENDGAME_API FEndWallModule {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> territoryID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 CM_SPACE_MAX;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float EDGE_OFFSET;
    
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    uint32 PointMaxNum;
    
    FEndWallModule();
};

