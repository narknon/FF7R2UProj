#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndVFXPositionInfoSetVolume_DebugComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndVFXPositionInfoSetVolume_DebugComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UEndVFXPositionInfoSetVolume_DebugComponent(const FObjectInitializer& ObjectInitializer);

};

