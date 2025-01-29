#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "EndEnvironmentPhysicsStaticMeshActor.h"
#include "EndAnimalRunBallActor.generated.h"

class AActor;
class UPrimitiveComponent;

UCLASS(Blueprintable)
class AEndAnimalRunBallActor : public AEndEnvironmentPhysicsStaticMeshActor {
    GENERATED_BODY()
public:
    AEndAnimalRunBallActor(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void OnComponentHitBall(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    
};

