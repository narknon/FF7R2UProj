#include "EndMiniGameSequenceActor.h"
#include "EndMiniGameSequencePlayer.h"

AEndMiniGameSequenceActor::AEndMiniGameSequenceActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UEndMiniGameSequencePlayer>(TEXT("AnimationPlayer"))) {
}


