#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndAerialNavDebugDrawComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndAerialNavDebugDrawComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UEndAerialNavDebugDrawComponent(const FObjectInitializer& ObjectInitializer);

};

