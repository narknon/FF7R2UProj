#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndCactusMissionConstantEnemyTerritoryData.h"
#include "EndCactusMissionRandomEnemyTerritoryData.h"
#include "EndCactusMissionMiniGameEnemyManager.generated.h"

class AEndFieldEnemyTerritoryActor;

UCLASS(Blueprintable)
class ENDGAME_API AEndCactusMissionMiniGameEnemyManager : public AActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<AEndFieldEnemyTerritoryActor*> DefaultEnemyTerritories;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<AEndFieldEnemyTerritoryActor*> BoxEnemyTerritories;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndCactusMissionRandomEnemyTerritoryData> RandomEnemyTerritories;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndCactusMissionConstantEnemyTerritoryData> ConstantEnemyTerritories;
    
public:
    AEndCactusMissionMiniGameEnemyManager(const FObjectInitializer& ObjectInitializer);

};

