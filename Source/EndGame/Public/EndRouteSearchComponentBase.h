#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndRouteSearchComponentBase.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndRouteSearchComponentBase : public UActorComponent {
    GENERATED_BODY()
public:
    UEndRouteSearchComponentBase(const FObjectInitializer& ObjectInitializer);

};

