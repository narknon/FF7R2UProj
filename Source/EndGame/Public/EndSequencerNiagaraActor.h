#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EndNiagaraActor.h"
#include "EndSequencerNiagaraActor.generated.h"

UCLASS(Blueprintable, NotPlaceable)
class ENDGAME_API AEndSequencerNiagaraActor : public AEndNiagaraActor {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FSoftObjectPath ResourcePath;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName ResourceName;
    
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName PlacedEventName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AttachActorName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AttachActorId;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FName AttachSocketName;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 DelayDestroyFrame;
    
    AEndSequencerNiagaraActor(const FObjectInitializer& ObjectInitializer);

};

