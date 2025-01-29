#pragma once
#include "CoreMinimal.h"
#include "EndCharacter.h"
#include "EndSwitchableMeshCharacter.generated.h"

UCLASS(Blueprintable)
class AEndSwitchableMeshCharacter : public AEndCharacter {
    GENERATED_BODY()
public:
    AEndSwitchableMeshCharacter(const FObjectInitializer& ObjectInitializer);

};

