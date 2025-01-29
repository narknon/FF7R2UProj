#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndDirectionalTriggerDrawComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndDirectionalTriggerDrawComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UEndDirectionalTriggerDrawComponent(const FObjectInitializer& ObjectInitializer);

};

