#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EEndEnvironmentPhysicsSpawnSplineConditionType.h"
#include "EndEnvironmentPhysicsSpawnPointData.h"
#include "EndNaviMapDataProviderInterface.h"
#include "Templates/SubclassOf.h"
#include "EndEnvironmentPhysicsSpawnSplineActor.generated.h"

class AEndEnvironmentPhysicsStaticMeshActor;
class UEndEnvironmentPhysicsSpawnSplineComponent;

UCLASS(Abstract, Blueprintable)
class AEndEnvironmentPhysicsSpawnSplineActor : public AActor, public IEndNaviMapDataProviderInterface {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EEndEnvironmentPhysicsSpawnSplineConditionType ConditionType;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<FName, TSubclassOf<AEndEnvironmentPhysicsStaticMeshActor>> PhysicsClassList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEndEnvironmentPhysicsSpawnPointData> SpawnPointList;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AutoDestroyTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bHighPriorityWaterBuoyancyCheck;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RotationRandomRange;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MaxLimitDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndEnvironmentPhysicsSpawnSplineComponent* SplineComponent;
    
public:
    AEndEnvironmentPhysicsSpawnSplineActor(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

