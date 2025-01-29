#pragma once
#include "CoreMinimal.h"
#include "Particles/Emitter.h"
#include "EndActorBaseInterface.h"
#include "EndSoundHandle.h"
#include "EndEmitter.generated.h"

class USoundBase;

UCLASS(Blueprintable)
class ENDGAME_API AEndEmitter : public AEmitter, public IEndActorBaseInterface {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndSoundHandle BeginSoundAudioComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndSoundHandle FinishSoundAudioComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FEndSoundHandle EventSoundAudioComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USoundBase* PlacementSoundAsset;
    
    AEndEmitter(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

