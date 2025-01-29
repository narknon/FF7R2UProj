#pragma once
#include "CoreMinimal.h"
#include "EndBattleDamageSourceExtensionComponent.h"
#include "EndBattleDamageSourceExtensionComponentTargetArrivalEnd.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndBattleDamageSourceExtensionComponentTargetArrivalEnd : public UEndBattleDamageSourceExtensionComponent {
    GENERATED_BODY()
public:
    UEndBattleDamageSourceExtensionComponentTargetArrivalEnd(const FObjectInitializer& ObjectInitializer);

};

