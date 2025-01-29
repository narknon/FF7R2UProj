#pragma once
#include "CoreMinimal.h"
#include "EndEnvironmentPhysicsSpawnPointData.generated.h"

USTRUCT(BlueprintType)
struct FEndEnvironmentPhysicsSpawnPointData {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName TargetPoint;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SpawnClassName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ItemId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName SpawnConditionStoryFlag;
    
    ENDGAME_API FEndEnvironmentPhysicsSpawnPointData();
};

