#pragma once
#include "CoreMinimal.h"
#include "EndFieldAddTriggerBoxMaker.h"
#include "EndFieldAddHookShotTriggerBoxMaker.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndFieldAddHookShotTriggerBoxMaker : public UEndFieldAddTriggerBoxMaker {
    GENERATED_BODY()
public:
    UEndFieldAddHookShotTriggerBoxMaker(const FObjectInitializer& ObjectInitializer);

};

