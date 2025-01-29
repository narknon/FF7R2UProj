#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndPBDBoxCollisionActor.generated.h"

class UBoxComponent;

UCLASS(Blueprintable)
class AEndPBDBoxCollisionActor : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UBoxComponent* CollisionComponent;
    
    AEndPBDBoxCollisionActor(const FObjectInitializer& ObjectInitializer);

};

