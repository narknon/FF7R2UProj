#pragma once
#include "CoreMinimal.h"
#include "EndFieldAddTriggerBoxMaker.h"
#include "EndFieldAddRedHoldMoveDeliveryTriggerBoxMaker.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndFieldAddRedHoldMoveDeliveryTriggerBoxMaker : public UEndFieldAddTriggerBoxMaker {
    GENERATED_BODY()
public:
    UEndFieldAddRedHoldMoveDeliveryTriggerBoxMaker(const FObjectInitializer& ObjectInitializer);

};

