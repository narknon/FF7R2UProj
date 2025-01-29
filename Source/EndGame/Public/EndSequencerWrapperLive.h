#pragma once
#include "CoreMinimal.h"
#include "EndSequencerWrapperEventBase.h"
#include "EndSequencerWrapperLive.generated.h"

UCLASS(Blueprintable, NonTransient)
class ENDGAME_API UEndSequencerWrapperLive : public UEndSequencerWrapperEventBase {
    GENERATED_BODY()
public:
    UEndSequencerWrapperLive();

};

