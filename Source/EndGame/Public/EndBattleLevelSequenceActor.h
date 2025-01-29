#pragma once
#include "CoreMinimal.h"
#include "LevelSequenceActor.h"
#include "EndActorBaseInterface.h"
#include "EndBattleLevelSequenceActor.generated.h"

class AEndBattleCameraActor;

UCLASS(Blueprintable)
class ENDGAME_API AEndBattleLevelSequenceActor : public ALevelSequenceActor, public IEndActorBaseInterface {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    AEndBattleCameraActor* CameraActor;
    
public:
    AEndBattleLevelSequenceActor(const FObjectInitializer& ObjectInitializer);

private:
    UFUNCTION(BlueprintCallable)
    void OnStop();
    
    UFUNCTION(BlueprintCallable)
    void OnFinished();
    

    // Fix for true pure virtual functions not being implemented
};

