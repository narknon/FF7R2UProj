#pragma once
#include "CoreMinimal.h"
#include "EndBattleDamageSourceExtensionComponent.h"
#include "EndBattleDamageSourceExtensionComponentPhysicsDamping.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBattleDamageSourceExtensionComponentPhysicsDamping : public UEndBattleDamageSourceExtensionComponent {
    GENERATED_BODY()
public:
    UEndBattleDamageSourceExtensionComponentPhysicsDamping(const FObjectInitializer& ObjectInitializer);

};

