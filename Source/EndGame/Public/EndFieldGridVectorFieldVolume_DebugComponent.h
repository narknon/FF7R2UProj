#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndFieldGridVectorFieldVolume_DebugComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndFieldGridVectorFieldVolume_DebugComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UEndFieldGridVectorFieldVolume_DebugComponent(const FObjectInitializer& ObjectInitializer);

};

