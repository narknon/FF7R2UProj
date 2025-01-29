#pragma once
#include "CoreMinimal.h"
#include "EndBattleDamageSourceExtensionComponent.h"
#include "EndBattleDamageSourceExtensionComponentMagneticTornado.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBattleDamageSourceExtensionComponentMagneticTornado : public UEndBattleDamageSourceExtensionComponent {
    GENERATED_BODY()
public:
    UEndBattleDamageSourceExtensionComponentMagneticTornado(const FObjectInitializer& ObjectInitializer);

};

