#pragma once
#include "CoreMinimal.h"
#include "EndBattleDamageSourceComponent.h"
#include "EndBattleDamageSourceComponentCircle.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBattleDamageSourceComponentCircle : public UEndBattleDamageSourceComponent {
    GENERATED_BODY()
public:
    UEndBattleDamageSourceComponentCircle(const FObjectInitializer& ObjectInitializer);

};

