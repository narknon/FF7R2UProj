#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndBuggySpawnPointData.h"
#include "EndBuggySpawnPointSplineActor.generated.h"

class UEndBuggySpawnPointSplineComponent;

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndBuggySpawnPointSplineActor : public AActor {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBuggySpawnPointSplineComponent* SplineComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndBuggySpawnPointData> SpawnList;
    
public:
    AEndBuggySpawnPointSplineActor(const FObjectInitializer& ObjectInitializer);

};

