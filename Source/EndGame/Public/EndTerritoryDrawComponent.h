#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EndTerritoryDrawComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class ENDGAME_API UEndTerritoryDrawComponent : public UActorComponent {
    GENERATED_BODY()
public:
    UEndTerritoryDrawComponent(const FObjectInitializer& ObjectInitializer);

};

