#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndBattleDamageSourceComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBattleDamageSourceComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UEndBattleDamageSourceComponent(const FObjectInitializer& ObjectInitializer);

};

