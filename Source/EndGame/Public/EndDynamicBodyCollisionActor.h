#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndDynamicBodyCollisionActor.generated.h"

class UEndDynamicBodyCollisionPrimitive;

UCLASS(Blueprintable, NotPlaceable)
class ENDGAME_API AEndDynamicBodyCollisionActor : public AActor {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, Transient, meta=(AllowPrivateAccess=true))
    TArray<UEndDynamicBodyCollisionPrimitive*> CollisionComponents;
    
public:
    AEndDynamicBodyCollisionActor(const FObjectInitializer& ObjectInitializer);

};

