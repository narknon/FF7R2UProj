#pragma once
#include "CoreMinimal.h"
#include "NavModifierVolume.h"
#include "EndNavModifierAvoidAnimalVolume.generated.h"

UCLASS(Blueprintable)
class AEndNavModifierAvoidAnimalVolume : public ANavModifierVolume {
    GENERATED_BODY()
public:
    AEndNavModifierAvoidAnimalVolume(const FObjectInitializer& ObjectInitializer);

};

