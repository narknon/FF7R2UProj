#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndSmoothTerrainCollisionVolume.generated.h"

class UBodySetup;
class UBoxComponent;
class UEndSmoothTerrainCollisionComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndSmoothTerrainCollisionVolume : public AActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MaxClimbHeight;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MinSlopeDiffDegrees;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MinDebugDrawSlopeDiffDegrees;
    
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UBoxComponent* BoxComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndSmoothTerrainCollisionComponent* CollisionComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    UBodySetup* TempBodySetup;
    
    AEndSmoothTerrainCollisionVolume(const FObjectInitializer& ObjectInitializer);

};

