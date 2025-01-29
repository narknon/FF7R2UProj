#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndActorBaseInterface.h"
#include "EndActorInterface.h"
#include "EndMergedSimpleCollisionActor.generated.h"

class UEndMergedSimpleCollisionComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndMergedSimpleCollisionActor : public AActor, public IEndActorInterface, public IEndActorBaseInterface {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndMergedSimpleCollisionComponent* MergedSimpleCollisionComponent;
    
public:
    AEndMergedSimpleCollisionActor(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

