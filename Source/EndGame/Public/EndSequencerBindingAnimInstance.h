#pragma once
#include "CoreMinimal.h"
#include "AnimSequencerInstance.h"
#include "EndSequencerBindingAnimInstance.generated.h"

UCLASS(Blueprintable, NonTransient)
class UEndSequencerBindingAnimInstance : public UAnimSequencerInstance {
    GENERATED_BODY()
public:
    UEndSequencerBindingAnimInstance();

};

