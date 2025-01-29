#pragma once
#include "CoreMinimal.h"
#include "EndBattleDamageSourceComponent.h"
#include "EndBattleDamageSourceComponentChangeHitReaction.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBattleDamageSourceComponentChangeHitReaction : public UEndBattleDamageSourceComponent {
    GENERATED_BODY()
public:
    UEndBattleDamageSourceComponentChangeHitReaction(const FObjectInitializer& ObjectInitializer);

};

