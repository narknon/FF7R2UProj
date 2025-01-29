#pragma once
#include "CoreMinimal.h"
#include "EndCactusMissionConditionData.h"
#include "EndCactusMissionConstantEnemyTerritoryData.generated.h"

class AEndFieldEnemyTerritoryActor;

USTRUCT(BlueprintType)
struct FEndCactusMissionConstantEnemyTerritoryData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    AEndFieldEnemyTerritoryActor* EnemyTerritory;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndCactusMissionConditionData ConditionData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool IsOnce;
    
    ENDGAME_API FEndCactusMissionConstantEnemyTerritoryData();
};

