#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AlphaBlend.h"
#include "EndSaveActorInterface.h"
#include "EndCameraSequenceActor.generated.h"

class UCameraComponent;
class ULevelSequence;

UCLASS(Blueprintable)
class ENDGAME_API AEndCameraSequenceActor : public AActor, public IEndSaveActorInterface {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UCameraComponent* CameraComponent;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    ULevelSequence* LevelSequence;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BlendInTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EAlphaBlendOption BlendInOption;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BlendOutTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    EAlphaBlendOption BlendOutOption;
    
public:
    AEndCameraSequenceActor(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable)
    void PlaySequence();
    
protected:
    UFUNCTION(BlueprintCallable)
    void OnPlayerFinished();
    

    // Fix for true pure virtual functions not being implemented
};

