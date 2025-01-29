#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndPBDCapsuleCollisionActor.generated.h"

class UCapsuleComponent;

UCLASS(Blueprintable)
class AEndPBDCapsuleCollisionActor : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UCapsuleComponent* CollisionComponent;
    
    AEndPBDCapsuleCollisionActor(const FObjectInitializer& ObjectInitializer);

};

