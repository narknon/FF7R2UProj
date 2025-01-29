#pragma once
#include "CoreMinimal.h"
#include "EndFieldAddTriggerBoxMaker.h"
#include "EndFieldAddRedHoldDeliveryTriggerBoxMaker.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndFieldAddRedHoldDeliveryTriggerBoxMaker : public UEndFieldAddTriggerBoxMaker {
    GENERATED_BODY()
public:
    UEndFieldAddRedHoldDeliveryTriggerBoxMaker(const FObjectInitializer& ObjectInitializer);

};

