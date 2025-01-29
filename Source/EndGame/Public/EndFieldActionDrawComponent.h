#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndFieldActionDrawComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndFieldActionDrawComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UEndFieldActionDrawComponent(const FObjectInitializer& ObjectInitializer);

};

