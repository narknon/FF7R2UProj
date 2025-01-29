#pragma once
#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "EndMobSwitchingArrowComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndMobSwitchingArrowComponent : public UArrowComponent {
    GENERATED_BODY()
public:
    UEndMobSwitchingArrowComponent(const FObjectInitializer& ObjectInitializer);

};

