#pragma once
#include "CoreMinimal.h"
#include "EndSequencerWrapperBase.h"
#include "EndSequencerWrapperEventBase.generated.h"

UCLASS(Blueprintable, NonTransient)
class ENDGAME_API UEndSequencerWrapperEventBase : public UEndSequencerWrapperBase {
    GENERATED_BODY()
public:
    UEndSequencerWrapperEventBase();

protected:
    UFUNCTION(BlueprintCallable)
    void StreamVolumeLoaded();
    
};

