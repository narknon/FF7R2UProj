#pragma once
#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "EndEnvironmentSkeletalMeshActor.h"
#include "EndThrowableReceiverEnvironmentSkeletalMeshActor.generated.h"

UCLASS(Blueprintable)
class ENDGAME_API AEndThrowableReceiverEnvironmentSkeletalMeshActor : public AEndEnvironmentSkeletalMeshActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName StoryFlag;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    bool bOnlyTriggerOnce;
    
    AEndThrowableReceiverEnvironmentSkeletalMeshActor(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void OnThrownObjectHitEvent(const FHitResult& HitResult);
    
};

