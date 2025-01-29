#include "EndWireReelActor.h"
#include "EndBoneAttachComponent.h"

AEndWireReelActor::AEndWireReelActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->BoneAttach = CreateDefaultSubobject<UEndBoneAttachComponent>(TEXT("BoneAttach"));
    this->WireReelAnimToPlay = NULL;
}

void AEndWireReelActor::SetWireState(EEndWireReelState InState) {
}


