#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndPBDIgnoreCollisionEdgeActor.generated.h"

class UEndPBDIgnoreCollisionEdgeComponent;

UCLASS(Blueprintable)
class AEndPBDIgnoreCollisionEdgeActor : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndPBDIgnoreCollisionEdgeComponent* IgnoreCollisionEdgeComponent;
    
    AEndPBDIgnoreCollisionEdgeActor(const FObjectInitializer& ObjectInitializer);

};

