#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndBattleAreaDrawComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndBattleAreaDrawComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UEndBattleAreaDrawComponent(const FObjectInitializer& ObjectInitializer);

};

