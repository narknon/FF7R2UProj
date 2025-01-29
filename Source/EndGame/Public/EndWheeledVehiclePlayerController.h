#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include "EndWheeledVehiclePlayerController.generated.h"

class UPrimitiveComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndWheeledVehiclePlayerController : public AActor {
    GENERATED_BODY()
public:
    AEndWheeledVehiclePlayerController(const FObjectInitializer& ObjectInitializer);

private:
    UFUNCTION(BlueprintCallable)
    void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    
};

