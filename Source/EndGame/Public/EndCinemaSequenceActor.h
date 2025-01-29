#pragma once
#include "CoreMinimal.h"
#include "LevelSequenceActor.h"
#include "EndCinemaSequenceActor.generated.h"

class UEndSequencerWrapperBase;
class USceneComponent;

UCLASS(Blueprintable)
class ENDGAME_API AEndCinemaSequenceActor : public ALevelSequenceActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FName> FieldCameraCuts;
    
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, meta=(AllowPrivateAccess=true))
    UEndSequencerWrapperBase* SequenceWrapper;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    USceneComponent* LayoutOffsetComponent;
    
public:
    AEndCinemaSequenceActor(const FObjectInitializer& ObjectInitializer);

};

