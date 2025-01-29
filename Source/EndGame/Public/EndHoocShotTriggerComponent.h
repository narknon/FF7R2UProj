#pragma once
#include "CoreMinimal.h"
#include "EndFieldActionTriggerComponent.h"
#include "EndHoocShotTriggerComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndHoocShotTriggerComponent : public UEndFieldActionTriggerComponent {
    GENERATED_BODY()
public:
    UEndHoocShotTriggerComponent(const FObjectInitializer& ObjectInitializer);

};

