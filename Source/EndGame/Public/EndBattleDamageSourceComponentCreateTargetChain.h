#pragma once
#include "CoreMinimal.h"
#include "EndBattleDamageSourceComponent.h"
#include "EndBattleDamageSourceComponentCreateTargetChain.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBattleDamageSourceComponentCreateTargetChain : public UEndBattleDamageSourceComponent {
    GENERATED_BODY()
public:
    UEndBattleDamageSourceComponentCreateTargetChain(const FObjectInitializer& ObjectInitializer);

};

