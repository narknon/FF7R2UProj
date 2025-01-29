#pragma once
#include "CoreMinimal.h"
#include "EndShapeComponent.h"
#include "EndDamageHitCollisionPrimitive.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndDamageHitCollisionPrimitive : public UEndShapeComponent {
    GENERATED_BODY()
public:
    UEndDamageHitCollisionPrimitive(const FObjectInitializer& ObjectInitializer);

};

