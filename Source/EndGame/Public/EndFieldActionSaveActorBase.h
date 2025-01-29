#pragma once
#include "CoreMinimal.h"
#include "EndFieldActionStateManagedActor.h"
#include "EndFieldActionSaveActorBase.generated.h"

class UEndNavModifierComponent;

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndFieldActionSaveActorBase : public AEndFieldActionStateManagedActor {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced, meta=(AllowPrivateAccess=true))
    UEndNavModifierComponent* ModifierVolume;
    
    AEndFieldActionSaveActorBase(const FObjectInitializer& ObjectInitializer);

};

