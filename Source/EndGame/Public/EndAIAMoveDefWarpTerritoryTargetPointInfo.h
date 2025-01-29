#pragma once
#include "CoreMinimal.h"
#include "EndAIAMoveDefWarpTerritoryTargetPointInfo.generated.h"

USTRUCT(BlueprintType)
struct FEndAIAMoveDefWarpTerritoryTargetPointInfo {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName territoryID;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> TargetPointNames;
    
    ENDGAME_API FEndAIAMoveDefWarpTerritoryTargetPointInfo();
};

