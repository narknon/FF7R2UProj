#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndBattleSummonTargetDrawComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndBattleSummonTargetDrawComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UEndBattleSummonTargetDrawComponent(const FObjectInitializer& ObjectInitializer);

};

