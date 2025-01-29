#pragma once
#include "CoreMinimal.h"
#include "EndBodyCollisionInterface.h"
#include "EndShapeComponent.h"
#include "EndAttackTargetCollisionPrimitive.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndAttackTargetCollisionPrimitive : public UEndShapeComponent, public IEndBodyCollisionInterface {
    GENERATED_BODY()
public:
    UEndAttackTargetCollisionPrimitive(const FObjectInitializer& ObjectInitializer);


    // Fix for true pure virtual functions not being implemented
};

