#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndActorBaseInterface.h"
#include "EndActorInterface.h"
#include "EndEnvironmentAccessorGroupActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndEnvironmentAccessorGroupActor : public AActor, public IEndActorBaseInterface, public IEndActorInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<AActor*> TargetActors;
    
    AEndEnvironmentAccessorGroupActor(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

