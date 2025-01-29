#pragma once
#include "CoreMinimal.h"
#include "EndBattleDamageSourceExtensionComponent.h"
#include "EndBattleDamageSourceExtensionComponentCheckPhysicsStable.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBattleDamageSourceExtensionComponentCheckPhysicsStable : public UEndBattleDamageSourceExtensionComponent {
    GENERATED_BODY()
public:
    UEndBattleDamageSourceExtensionComponentCheckPhysicsStable(const FObjectInitializer& ObjectInitializer);

};

