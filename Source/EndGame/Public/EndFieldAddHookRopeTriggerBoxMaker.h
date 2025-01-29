#pragma once
#include "CoreMinimal.h"
#include "EndFieldAddTriggerBoxMaker.h"
#include "EndFieldAddHookRopeTriggerBoxMaker.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndFieldAddHookRopeTriggerBoxMaker : public UEndFieldAddTriggerBoxMaker {
    GENERATED_BODY()
public:
    UEndFieldAddHookRopeTriggerBoxMaker(const FObjectInitializer& ObjectInitializer);

};

