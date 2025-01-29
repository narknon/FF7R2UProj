#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndActorBaseInterface.h"
#include "EndCrowdActorInterface.h"
#include "EndCrowdActorSoundEntry.h"
#include "EndOptimizeAnimActorInterface.h"
#include "EndCrowdActorBase.generated.h"

class UFXSystemAsset;

UCLASS(Blueprintable)
class ENDGAME_API AEndCrowdActorBase : public AActor, public IEndCrowdActorInterface, public IEndActorBaseInterface, public IEndOptimizeAnimActorInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FadeInWaitTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float OverrideFadeInTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float OverrideFadeOutTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UFXSystemAsset* EffectTemplate;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndCrowdActorSoundEntry SoundEntry;
    
    AEndCrowdActorBase(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void Stop(float BlendTime, bool bUseFade);
    
    UFUNCTION(BlueprintCallable)
    void Play(float BlendTime, bool bUseFade);
    

    // Fix for true pure virtual functions not being implemented
};

