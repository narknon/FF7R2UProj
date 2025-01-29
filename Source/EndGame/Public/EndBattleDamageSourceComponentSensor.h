#pragma once
#include "CoreMinimal.h"
#include "EndBattleDamageSourceComponent.h"
#include "EndBattleDamageSourceComponentSensor.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBattleDamageSourceComponentSensor : public UEndBattleDamageSourceComponent {
    GENERATED_BODY()
public:
    UEndBattleDamageSourceComponentSensor(const FObjectInitializer& ObjectInitializer);

};

