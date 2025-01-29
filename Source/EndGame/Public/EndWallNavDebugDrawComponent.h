#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndWallNavDebugDrawComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndWallNavDebugDrawComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UEndWallNavDebugDrawComponent(const FObjectInitializer& ObjectInitializer);

};

