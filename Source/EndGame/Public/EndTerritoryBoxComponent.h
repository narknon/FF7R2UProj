#pragma once
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "EndTerritoryBoxComponent.generated.h"

UCLASS(Blueprintable, EditInlineNew, ClassGroup=Custom, meta=(BlueprintSpawnableComponent))
class UEndTerritoryBoxComponent : public UBoxComponent {
    GENERATED_BODY()
public:
    UEndTerritoryBoxComponent(const FObjectInitializer& ObjectInitializer);

};

