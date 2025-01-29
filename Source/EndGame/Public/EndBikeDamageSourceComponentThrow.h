#pragma once
#include "CoreMinimal.h"
#include "EndBikeDamageSourceComponent.h"
#include "EndBikeDamageSourceComponentThrow.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBikeDamageSourceComponentThrow : public UEndBikeDamageSourceComponent {
    GENERATED_BODY()
public:
    UEndBikeDamageSourceComponentThrow(const FObjectInitializer& ObjectInitializer);

};

