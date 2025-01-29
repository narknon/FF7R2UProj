#pragma once
#include "CoreMinimal.h"
#include "EndBikeDamageSourceComponent.h"
#include "EndBikeDamageSourceComponentGrenade.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBikeDamageSourceComponentGrenade : public UEndBikeDamageSourceComponent {
    GENERATED_BODY()
public:
    UEndBikeDamageSourceComponentGrenade(const FObjectInitializer& ObjectInitializer);

};

