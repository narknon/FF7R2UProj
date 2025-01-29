#pragma once
#include "CoreMinimal.h"
#include "VFXNiagaraActor.h"
#include "EndNiagaraActor.generated.h"

class USoundBase;

UCLASS(Blueprintable)
class ENDGAME_API AEndNiagaraActor : public AVFXNiagaraActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USoundBase* m_PlacementSoundAsset;
    
    AEndNiagaraActor(const FObjectInitializer& ObjectInitializer);

};

