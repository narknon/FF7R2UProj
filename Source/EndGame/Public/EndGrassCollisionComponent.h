#pragma once
#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "EndGrassCollisionComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndGrassCollisionComponent : public UPrimitiveComponent {
    GENERATED_BODY()
public:
    UEndGrassCollisionComponent(const FObjectInitializer& ObjectInitializer);

};

