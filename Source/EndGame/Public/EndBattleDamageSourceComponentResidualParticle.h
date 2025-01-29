#pragma once
#include "CoreMinimal.h"
#include "EndBattleDamageSourceComponentTraceHit.h"
#include "EndBattleDamageSourceComponentResidualParticle.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBattleDamageSourceComponentResidualParticle : public UEndBattleDamageSourceComponentTraceHit {
    GENERATED_BODY()
public:
    UEndBattleDamageSourceComponentResidualParticle(const FObjectInitializer& ObjectInitializer);

};

