#pragma once
#include "CoreMinimal.h"
#include "EndBikeDamageSourceComponent.h"
#include "EndBikeDamageSourceComponentDrive.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBikeDamageSourceComponentDrive : public UEndBikeDamageSourceComponent {
    GENERATED_BODY()
public:
    UEndBikeDamageSourceComponentDrive(const FObjectInitializer& ObjectInitializer);

};

