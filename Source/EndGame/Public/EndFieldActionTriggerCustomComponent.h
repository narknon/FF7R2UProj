#pragma once
#include "CoreMinimal.h"
#include "EndFieldActionTriggerComponent.h"
#include "EndFieldActionTriggerCustomComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndFieldActionTriggerCustomComponent : public UEndFieldActionTriggerComponent {
    GENERATED_BODY()
public:
    UEndFieldActionTriggerCustomComponent(const FObjectInitializer& ObjectInitializer);

};

