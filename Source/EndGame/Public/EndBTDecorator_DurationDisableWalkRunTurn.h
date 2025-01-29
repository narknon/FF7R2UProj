#pragma once
#include "CoreMinimal.h"
#include "EndBTDecorator_DurationSuspendable.h"
#include "EndBTDecorator_DurationDisableWalkRunTurn.generated.h"

UCLASS(Blueprintable)
class UEndBTDecorator_DurationDisableWalkRunTurn : public UEndBTDecorator_DurationSuspendable {
    GENERATED_BODY()
public:
    UEndBTDecorator_DurationDisableWalkRunTurn();

};

