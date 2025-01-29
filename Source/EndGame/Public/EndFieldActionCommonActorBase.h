#pragma once
#include "CoreMinimal.h"
#include "EndFieldActionStateManagedActor.h"
#include "EndFieldActionCommonActorBase.generated.h"

UCLASS(Abstract, Blueprintable)
class ENDGAME_API AEndFieldActionCommonActorBase : public AEndFieldActionStateManagedActor {
    GENERATED_BODY()
public:
    AEndFieldActionCommonActorBase(const FObjectInitializer& ObjectInitializer);

};

