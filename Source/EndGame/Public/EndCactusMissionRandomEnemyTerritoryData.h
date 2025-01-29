#pragma once
#include "CoreMinimal.h"
#include "EndCactusMissionConditionData.h"
#include "EndCactusMissionEnemyTerritoryActorData.h"
#include "EndCactusMissionRandomEnemyTerritoryData.generated.h"

USTRUCT(BlueprintType)
struct FEndCactusMissionRandomEnemyTerritoryData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndCactusMissionEnemyTerritoryActorData> EnemyTerritories;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndCactusMissionConditionData ConditionData;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool IsOnce;
    
    ENDGAME_API FEndCactusMissionRandomEnemyTerritoryData();
};

