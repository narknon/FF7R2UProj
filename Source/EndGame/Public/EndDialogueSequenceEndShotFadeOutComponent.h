#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndDialogueSequenceEndShotFadeOutComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndDialogueSequenceEndShotFadeOutComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UEndDialogueSequenceEndShotFadeOutComponent(const FObjectInitializer& ObjectInitializer);

};

