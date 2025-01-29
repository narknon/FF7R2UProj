#pragma once
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EndPBDIgnoreCollisionEdgeComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndPBDIgnoreCollisionEdgeComponent : public UBoxComponent {
    GENERATED_BODY()
public:
    UEndPBDIgnoreCollisionEdgeComponent(const FObjectInitializer& ObjectInitializer);

};

