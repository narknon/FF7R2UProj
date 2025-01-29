#pragma once
#include "CoreMinimal.h"
#include "EndBattleDamageSourceComponentTraceHit.h"
#include "EndBattleDamageSourceComponentRocketPunch.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBattleDamageSourceComponentRocketPunch : public UEndBattleDamageSourceComponentTraceHit {
    GENERATED_BODY()
public:
    UEndBattleDamageSourceComponentRocketPunch(const FObjectInitializer& ObjectInitializer);

};

