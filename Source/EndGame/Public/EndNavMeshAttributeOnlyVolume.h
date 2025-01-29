#pragma once
#include "CoreMinimal.h"
#include "NavModifierVolume.h"
#include "EndNavMeshAttributeOnlyVolume.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class AEndNavMeshAttributeOnlyVolume : public ANavModifierVolume {
    GENERATED_BODY()
public:
    AEndNavMeshAttributeOnlyVolume(const FObjectInitializer& ObjectInitializer);

};

