#pragma once
#include "CoreMinimal.h"
#include "EndCactusMissionEnemyTerritoryActorData.generated.h"

class AEndFieldEnemyTerritoryActor;

USTRUCT(BlueprintType)
struct FEndCactusMissionEnemyTerritoryActorData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    AEndFieldEnemyTerritoryActor* EnemyTerritory;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 Rate;
    
    ENDGAME_API FEndCactusMissionEnemyTerritoryActorData();
};

