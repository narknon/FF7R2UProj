#pragma once
#include "CoreMinimal.h"
#include "EndBattleDamageSourceExtensionComponent.h"
#include "EndBattleDamageSourceExtensionComponentFollowOwnerPhysicsObject.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBattleDamageSourceExtensionComponentFollowOwnerPhysicsObject : public UEndBattleDamageSourceExtensionComponent {
    GENERATED_BODY()
public:
    UEndBattleDamageSourceExtensionComponentFollowOwnerPhysicsObject(const FObjectInitializer& ObjectInitializer);

};

