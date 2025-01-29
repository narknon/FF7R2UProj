#include "EndNavModifierAvoidAnimalVolume.h"
#include "EndNavAreaWildAnimal.h"

AEndNavModifierAvoidAnimalVolume::AEndNavModifierAvoidAnimalVolume(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
    this->bIsEditorOnlyActor = true;
    this->AreaClass = UEndNavAreaWildAnimal::StaticClass();
}


