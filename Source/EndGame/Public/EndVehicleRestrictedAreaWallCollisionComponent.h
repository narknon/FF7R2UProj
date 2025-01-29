#pragma once
#include "CoreMinimal.h"
#include "EndUniqueSimpleCollisionComponent.h"
#include "EndVehicleRestrictedAreaWallCollisionComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndVehicleRestrictedAreaWallCollisionComponent : public UEndUniqueSimpleCollisionComponent {
    GENERATED_BODY()
public:
    UEndVehicleRestrictedAreaWallCollisionComponent(const FObjectInitializer& ObjectInitializer);

};

