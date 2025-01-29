#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndPBDSphereCollisionActor.generated.h"

class USphereComponent;

UCLASS(Blueprintable)
class AEndPBDSphereCollisionActor : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USphereComponent* CollisionComponent;
    
    AEndPBDSphereCollisionActor(const FObjectInitializer& ObjectInitializer);

};

