#pragma once
#include "CoreMinimal.h"
#include "EndBikeDamageSourceComponent.h"
#include "EndBikeDamageSourceComponentHoming.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBikeDamageSourceComponentHoming : public UEndBikeDamageSourceComponent {
    GENERATED_BODY()
public:
    UEndBikeDamageSourceComponentHoming(const FObjectInitializer& ObjectInitializer);

};

