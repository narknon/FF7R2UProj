#include "EndDialogueSequenceActor.h"
#include "EndDialogueSequencePlayer.h"

AEndDialogueSequenceActor::AEndDialogueSequenceActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UEndDialogueSequencePlayer>(TEXT("AnimationPlayer"))) {
    this->bConstraintAspectRatio = true;
}


