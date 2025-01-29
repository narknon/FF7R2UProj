#pragma once
#include "CoreMinimal.h"
#include "EndShapeComponent.h"
#include "EndPhysicsBlockPrimitive.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndPhysicsBlockPrimitive : public UEndShapeComponent {
    GENERATED_BODY()
public:
    UEndPhysicsBlockPrimitive(const FObjectInitializer& ObjectInitializer);

};

