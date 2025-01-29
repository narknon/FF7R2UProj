#pragma once
#include "CoreMinimal.h"
#include "EndEnvironmentPhysicsStaticMeshActor.h"
#include "EndBattlePhysicsStaticMeshActor.generated.h"

class UEndBattleDamageSourceCollisionComponent;

UCLASS(Abstract, Blueprintable)
class AEndBattlePhysicsStaticMeshActor : public AEndEnvironmentPhysicsStaticMeshActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndBattleDamageSourceCollisionComponent* DamageSourceCollision;
    
public:
    AEndBattlePhysicsStaticMeshActor(const FObjectInitializer& ObjectInitializer);

};

