#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndPBDIgnoreCollisionActor.generated.h"

class UEndPBDIgnoreCollisionComponent;

UCLASS(Blueprintable)
class AEndPBDIgnoreCollisionActor : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndPBDIgnoreCollisionComponent* IgnoreCollisionComponent;
    
    AEndPBDIgnoreCollisionActor(const FObjectInitializer& ObjectInitializer);

};

