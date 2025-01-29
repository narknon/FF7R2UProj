#pragma once
#include "CoreMinimal.h"
#include "EndBattleDamageSourceExtensionComponentDestroyOmenEffect.h"
#include "EndBattleDamageSourceExtensionComponentDestroyOmenEmissive.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBattleDamageSourceExtensionComponentDestroyOmenEmissive : public UEndBattleDamageSourceExtensionComponentDestroyOmenEffect {
    GENERATED_BODY()
public:
    UEndBattleDamageSourceExtensionComponentDestroyOmenEmissive(const FObjectInitializer& ObjectInitializer);

};

