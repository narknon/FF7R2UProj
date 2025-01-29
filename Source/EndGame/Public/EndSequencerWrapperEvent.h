#pragma once
#include "CoreMinimal.h"
#include "EndSequencerWrapperEventBase.h"
#include "EndSequencerWrapperEvent.generated.h"

UCLASS(Blueprintable, NonTransient)
class UEndSequencerWrapperEvent : public UEndSequencerWrapperEventBase {
    GENERATED_BODY()
public:
    UEndSequencerWrapperEvent();

};

